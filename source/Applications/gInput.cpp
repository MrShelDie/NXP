/*
 * Copyright 2003-20xx Haute �cole ARC Ing�ni�rie, Switzerland. 
 * All rights reserved.

 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Haute �cole ARC Ing�ni�rie nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

/*----------------------------------------------------------
Copyright 2003-201x Haute �cole ARC Ing�ni�rie, Switzerland. 
All rights reserved.
------------------------------------------------------------
Nom du fichier :	gInput.c
Auteur et Date :	Monnerat Serge 8.5.20xx

Description dans le fichier gInput.h
------------------------------------------------------------
*/

extern "C"
{
#include "Modules/mDelay.h"
}

#include "gInput.h"
#include "gMBox.h"

#define VECTORS_SIZE 20


static void CopyVector(VectorFlagged &dst, Vector &src)
{
	dst.is_interf = false;
	dst.m_index = (int)src.m_index;
	dst.m_x0 = src.m_x0;
	dst.m_x1 = src.m_x1;
	dst.m_y0 = src.m_y0;
	dst.m_y1 = src.m_y1;
}

// Копирует pixy векторы в массив помеченных векторов, возвращает их скопированное кол-во
static int CopyPixyVectorsToVectorFlagged(Vector vectors_pixy[], VectorFlagged vectors[], uint8_t numVectors)
{
	uint8_t i;

	for (i = 0; i < numVectors && i < VECTORS_SIZE; i++)
		CopyVector(vectors[i], vectors_pixy[i]);
	return ((int)i);
}

void ifStopLine(Vector new_vector)
{
	if (((new_vector.m_x0 == gInput.chosen_vectors[0].m_x1 && new_vector.m_y0 == gInput.chosen_vectors[0].m_y1) ||
		(new_vector.m_x1 == gInput.chosen_vectors[0].m_x1 && new_vector.m_y0 == gInput.chosen_vectors[0].m_y1)) &&
		((new_vector.m_x0 == gInput.chosen_vectors[1].m_x1 && new_vector.m_y0 == gInput.chosen_vectors[1].m_y1) ||
		(new_vector.m_x1 == gInput.chosen_vectors[1].m_x1 && new_vector.m_y0 == gInput.chosen_vectors[1].m_y1)))
	{
		gCompute.StopKey1 = true;
	}
	gCompute.StopKey1 = false;
}


// Откидывает шумовые векторы
static int FiltreVectors(Vector vectors_pixy[], VectorFlagged vectors[], uint8_t numVectors)
{
	int not_interf_count = 0;

	bool	is_vector_found;
	uint8_t i;
	int		j;

	for (i = 0; i < numVectors; i++)
	{
		is_vector_found = false;

		for (j = 0; j < VECTORS_SIZE; j++)
		{
			if (vectors_pixy[i].m_index == vectors[j].m_index)
			{
				CopyVector(vectors[j], vectors_pixy[i]);
				is_vector_found = true;
				not_interf_count++;
				break;
			}

			ifStopLine(vectors_pixy[i]); // !!!Проверка стоп линии!!!

		}
		if (!is_vector_found)
			vectors[j].is_interf = true;
		else
			vectors[j].is_interf = false;
	}
	return (not_interf_count);
}

static void	Choose1DirectVector(const VectorFlagged vectors[])
{
	int	i = -1;

	while (vectors[++i].is_interf);
	gInput.chosen_vectors[0] = vectors[i];
	gInput.chosen_count = 1;
}

// Функция из векторов, прошедших валидацию, находит два вектора,
// чей конец будет находиться выше концов остальных векторов
static void Choose2DirectVectors(int not_interf_count, const VectorFlagged vectors[])
{
	int	i = -1;

	// Записываем первые два вектора, не являющиеся помехами
	while (vectors[++i].is_interf);
	gInput.chosen_vectors[0] = vectors[i];
	while (vectors[++i].is_interf);
	gInput.chosen_vectors[1] = vectors[i];

	not_interf_count -= 2;

	// Проверяем остальные векторы
	while (not_interf_count > 0)
	{
		i++;
		if (!vectors[i].is_interf)
		{
			if (vectors[i].m_y1 < gInput.chosen_vectors[0].m_y1)
				gInput.chosen_vectors[0] = vectors[i];
			else if (vectors[i].m_y1 < gInput.chosen_vectors[1].m_y1)
				gInput.chosen_vectors[1] = vectors[i];
			not_interf_count--;
		}
	}
	gInput.chosen_count = 2;
	gInput.chosen_vectors[2].m_index = -1;
}

static void SortChosenVectors()
{
	VectorFlagged temp;

	if (gInput.chosen_vectors[0].m_x1 > gInput.chosen_vectors[1].m_x1)
	{
		temp = gInput.chosen_vectors[0];
		gInput.chosen_vectors[0] = gInput.chosen_vectors[1];
		gInput.chosen_vectors[1] = temp;
	}
}

void gInput_Setup(void)
{

}

void gInput_Execute(Pixy2SPI_SS &pixy)
{
	Int16 			input_delay_nb;
	int				not_interf_vector_count = 0;
	VectorFlagged	vectors[VECTORS_SIZE];

	input_delay_nb = mDelay_GetDelay(kPit1, INPUT_DURATION);

	while (!mDelay_IsDelayDone(kPit1, input_delay_nb))
	{
		// Получает векторы с камеры в pixy.line.vectors
		pixy.line.getAllFeatures(LINE_VECTOR, true);

		if (not_interf_vector_count == 0)
		{
			not_interf_vector_count = CopyPixyVectorsToVectorFlagged(pixy.line.vectors, vectors, pixy.line.numVectors);
			mDelay_ReStart(kPit1, input_delay_nb, INPUT_DURATION);
		}
		else
			not_interf_vector_count = FiltreVectors(pixy.line.vectors, vectors, pixy.line.numVectors);
	}

	if (not_interf_vector_count > 1)
	{
		Choose2DirectVectors(not_interf_vector_count, vectors);
		SortChosenVectors();
	}
	else
		Choose1DirectVector(vectors);

	mDelay_DelayRelease(kPit1, input_delay_nb);
}

//void gInput_Execute(Pixy2SPI_SS &pixy)
//{
//	int				not_interf_vector_count = 0;
//	VectorFlagged	vectors[VECTORS_SIZE];
//
//	pixy.line.getAllFeatures(LINE_VECTOR, true);
//	not_interf_vector_count = CopyPixyVectorsToVectorFlagged(pixy.line.vectors, vectors, pixy.line.numVectors);
//
//
//	if (not_interf_vector_count > 1)
//	{
//		Choose2DirectVectors(not_interf_vector_count, vectors);
//		SortChosenVectors();
//	}
//	else
//		Choose1DirectVector(vectors);
//}
