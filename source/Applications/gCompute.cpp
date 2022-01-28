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

/*
 * Nom du fichier :	gCompute.c
 * Auteur et Date :	Monnerat Serge 8.5.20xx

 * Description dans le fichier gCompute.h
------------------------------------------------------------
*/

#include "gCompute.h"
#include "gMBox.h"
#include <stdio.h>
#include <cmath>

#define pi 			3.1415926535
#define PIXY_MID_X 	39
#define PIXY_MAX_Y 	51
#define DROP_MAX	50

//-----------------------------------------------------------------------------
// Configuration du gestionnaire
//-----------------------------------------------------------------------------
void gCompute_Setup(void)
{
}

//-----------------------------------------------------------------------------
// Ex�cution du gestionnaire
//-----------------------------------------------------------------------------
//void gCompute_Execute(void)
//{
//	printf("(%d, %d) ", gInput.chosen_vectors[0].m_x0, gInput.chosen_vectors[0].m_y0);
//	printf("(%d, %d)\n", gInput.chosen_vectors[0].m_x1, gInput.chosen_vectors[0].m_y1);
//
//	printf("(%d, %d) ", gInput.chosen_vectors[1].m_x0, gInput.chosen_vectors[1].m_y0);
//	printf("(%d, %d)\n", gInput.chosen_vectors[1].m_x1, gInput.chosen_vectors[1].m_y1);
//
//	printf("----------------------------\n");
//}

static void compute_main_vector(int x, int y, int *dx, int *dy)
{
	*dx = x - PIXY_MID_X;
	*dy = (y - PIXY_MAX_Y) * (-1);
}

static int left_or_right(int dx)
{
	if (dx<0) return 1;
	else return -1;
}

static int compute_angle(int dx, int dy)
{
	return acos(dy/(sqrt(dx*dx + dy*dy)))/pi * 180 * left_or_right(dx);
}

static void get_main_point(int *x, int *y)
{
	*x = (gInput.chosen_vectors[1].m_x1 + gInput.chosen_vectors[0].m_x1) / 2;
	*y = (gInput.chosen_vectors[1].m_y1 + gInput.chosen_vectors[0].m_y1) / 2;
}

void gCompute_Execute(void)
{
	int	x, y;
	int dx, dy;

	get_main_point(&x, &y);
	compute_main_vector(x, y, &dx, &dy);

#ifdef _DEBUG_
	printf("x = %d\ty = %d\ndx = %d,\tdy = %d\n", x, y, dx, dy);
#endif

	gCompute.turn_angle = compute_angle(dx, dy);
}

bool CheckStopLine()
{
	for (int i = 0; i < PIXEL_LINE_SIZE - 1; i++)
	{
		if ((gInput.pixel_line[i] != -1 && gInput.pixel_line[i + 1] != -1)
			&& (abs(gInput.pixel_line[i] - gInput.pixel_line[i + 1]) > DROP_MAX)
		)
			return (true);
	}
	return (false);
}
