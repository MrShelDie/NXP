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
Nom du fichier : 	gMBox.h	
Auteur et Date :	Monnerat Serge 8.5.20xx

But : Bo�te aux lettres

Modifications
Date		Faite	Ctrl		Description
------------------------------------------------------------
*/

#ifndef __GMBOX__
#define __GMBOX__

#include "Utils/def.h"

//-----------------------------------------------------------------------------
// Structure du gestionnaire Input
//-----------------------------------------------------------------------------

#define kNbOfSw 8
#define PIXEL_LINE_SIZE 40
#include <stdint.h>


struct VectorFlagged
{
	bool	is_interf;		// Помеха ли это
	bool    is_stopline     // Стоп линия ли
	uint8_t m_x0;
	uint8_t m_y0;
	uint8_t m_x1;
	uint8_t m_y1;
	int		m_index;
	uint8_t m_flags;
};


typedef struct
{
	struct VectorFlagged	chosen_vectors[2];
	int						chosen_count;
	int						pixel_line[PIXEL_LINE_SIZE];
} InputStruct;

extern InputStruct gInput;

#define kNbOfErr 8

typedef struct
{
  int turn_angle;
  bool StopKey1 = false;       // Найдена ли стоплиния сейчас
  bool StopKey2 = false;       // Была ли найдена стоплиния раньше
} ComputeStruct;

extern ComputeStruct gCompute;

void ResetPixelLine();

#endif /* __GMBOX__ */
