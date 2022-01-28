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
 * o Neither the name of NHaute �cole ARC Ing�ni�rie nor the names of its
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
Nom du fichier :	gOutput.c
Auteur et Date :	Monnerat Serge 8.5.20xx

Description dans le fichier gOutput.h
------------------------------------------------------------
*/

#include "gOutput.h"
#include "gMBox.h"
#include "Utils/def.h"

//-------------------------------------------------------------------------
// D�claration des constantes
//-------------------------------------------------------------------------
#define MAX_SERVO_ANGLE 42.21
//-----------------------------------------------------------------------------
// D�claration des variables globales
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Configuration du gestionnaire
//-----------------------------------------------------------------------------
void gOutput_Setup(void)
{
}

float compute_servo_duty()
{
	if (gCompute.turn_angle < -MAX_SERVO_ANGLE)
		return (-1);
	if (gCompute.turn_angle > MAX_SERVO_ANGLE)
		return (1);
	else
		return (gCompute.turn_angle / MAX_SERVO_ANGLE);
}
//-----------------------------------------------------------------------------
// Ex�cution du gestionnaire
//-----------------------------------------------------------------------------
void gOutput_Execute(void)
{
	float servo_duty = compute_servo_duty();
	mTimer_SetServoDuty(0, servo_duty);

#ifdef _DEBUG_
	printf("Angle = %d\n", gCompute.turn_angle);
	printf("Duty = %d\n", (int)(servo_duty * 100));
	printf("---------------------------------------\n");
#endif
}
