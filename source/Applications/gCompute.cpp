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

#define MIN(X, Y) X < Y ? X : Y

extern "C"
{
#include "Modules/mTimer.h"
}

void gCompute_Setup(void)
{

}

static void setMainVectorDeviation(int x, int y, int &dx, int &dy)
{
	dx = x - PIXY_MID_X;
	dy = (y - PIXY_MAX_Y) * (-1);
}

static int getLeftOrRightDirection(int dx)
{
	if (dx<0) return 1;
	else return -1;
}

static int computeAngleByMainVectorDeviation(int dx, int dy)
{
	return acos(dy/(sqrt(dx*dx + dy*dy)))/pi * 180 * getLeftOrRightDirection(dx);
}

static void setMainPoint(int &x, int &y)
{
	uint8_t	x0 = gInput.chosen_vectors[0].m_y1 < gInput.chosen_vectors[0].m_y0
			? gInput.chosen_vectors[0].m_x1
			: gInput.chosen_vectors[0].m_x0;

	uint8_t	x1 = gInput.chosen_vectors[1].m_y1 < gInput.chosen_vectors[1].m_y0
				? gInput.chosen_vectors[1].m_x1
				: gInput.chosen_vectors[1].m_x0;

	uint8_t	y0 = MIN(gInput.chosen_vectors[0].m_y1, gInput.chosen_vectors[0].m_y0);
	uint8_t	y1 = MIN(gInput.chosen_vectors[1].m_y1, gInput.chosen_vectors[1].m_y0);

	x = (x0 + x1) / 2;
	y = (y0 + y1) / 2;
}

static int	getAngleByOneVector()
{
	if (gInput.chosen_vectors[0].m_x0 <= gInput.chosen_vectors[0].m_x1)
		return (MAX_SERVO_ANGLE * -1);
	else
		return (MAX_SERVO_ANGLE);
}


void checkStopLine(void)
{
	if(gCompute.StopKey1 == true)
		gCompute.StopKey2 = true;
	else if(gCompute.StopKey1 == false && gCompute.StopKey2 == true)
		mTimer_SetMotorDuty(0, 0);  //остановка
}

void gCompute_Execute(void)
{
	int	x, y;
	int dx, dy;

	if (gInput.chosen_count == 2)
	{
		setMainPoint(x, y);
		setMainVectorDeviation(x, y, dx, dy);
		gCompute.turn_angle = computeAngleByMainVectorDeviation(dx, dy);
	}
	else if (gInput.chosen_count == 1)
		gCompute.turn_angle = getAngleByOneVector();
	checkStopLine();	//Пора ли останавливаться
}
