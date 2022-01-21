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

#include "gInput.h"
#include "gMBox.h"

#define VECTORS_SIZE 20

// Создать свою структуру Vector, которая будет хранить флаг
static Vector	vectors[VECTORS_SIZE];
static int		vectors_remaind = 0;
static int		chosen_vectors[2];

static void CopyVector(Vector *dst, Vector *src)
{
	dst->m_index = src->m_index;
	dst->m_x0 = src->m_x0;
	dst->m_x1 = src->m_x1;
	dst->m_y0 = src->m_y0;
	dst->m_y1 = src->m_y1;
}

static void ClearVector(Vector *vector)
{
	vector->m_index = 0;
	vector->
}

static void ReadVectorsIdx(Vector *vectors_pixy, uint8_t numVectors)
{
	for (uint8_t i; i < numVectors && i < VECTORS_SIZE; i++)
		CopyVector(&vectors[i], &vectors_pixy[i]);
}


// Откидывает шумовые векторы
static void Validation(Vector *vectors_pixy, uint8_t numVectors)
{
	vectors_remaind = 0;

	bool	is_found;
	uint8_t i;
	int		j;

	for (i = 0; i < numVectors; i++)
	{
		is_found = false;

		for (j = 0; j < VECTORS_SIZE; j++)
		{
			if (vectors_pixy[i].m_index == vectors[j].m_index)
			{
				is_found = true;
				vectors_idx_remaind++;
				break;
			}
		}

		if (!is_found)
			vectors[j] = -1;
	}
}


void gInput_Setup(void)
{
	for (int i = 0; i < VECTORS_SIZE; i++)
		vectors_idx[i] = -1;
}

void choosing_vectors()
{
	int i = 0;
	while(vectors_idx_remaind!=2)
	{
		if (vectors_idx[i] != -1)chosen_vectors[]=vectors_idx[i];
	}
}


void gInput_Execute(Pixy2SPI_SS pixy)
{
	pixy.line.getAllFeatures(LINE_VECTOR, true);

	while (vectors_idx_remaind < 2)
	{
		ReadVectorsIdx(pixy.line.vectors, pixy.line.numVectors);
		Validation(pixy.line.vectors, pixy.line.numVectors);
	}
}
