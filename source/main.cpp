
/*
 * Copyright 2003-20xx Haute �cole ARC Ing�ni�rie, Switzerland. 
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
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
 */

/**
 * @file    nxpcup_ARC.c
 * @brief   Application entry point.
 */

extern "C"
{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"

#include "Modules/mSpi.h"
#include "Modules/mDac.h"
#include "Modules/mAccelMagneto.h"
#include "Modules/mGyro.h"
#include "Modules/mTimer.h"
#include "Modules/mCpu.h"
#include "Modules/mSwitch.h"
#include "Modules/mLeds.h"
#include "Modules/mAd.h"
#include "Modules/mDelay.h"
#include "Modules/mRS232.h"
#include "Modules/mVL6180x.h"
}

#include "Applications/gInput.h"
#include "Applications/gCompute.h"
#include "Applications/gOutput.h"
#include "Utils/def.h"
#include "Pixy/Pixy2SPI_SS.h"

#include "Applications/gMBox.h"

#define K_MAIN_INTERVAL (100 / kPit1Period)


//void Test()
//{
//	//Pixycam --> create an instance
//	Pixy2SPI_SS pixy;
//	pixy.init();
//	pixy.version->print();
//
//	PRINTF("Hello World\n");
//	pixy.setLED(255, 0, 0); // Set RGB LED of Pixy to red
//}


int main(void)
{
	//--------------------------------------------------------------------
	// Device and card setup
	//--------------------------------------------------------------------
	// PLL Config --> CPU 100MHz, bus and periph 50MH z
	mCpu_Setup();

	// Config and start switches and pushers
	mSwitch_Setup();
	mSwitch_Open();

	// Config and start of LEDs
	mLeds_Setup();
	mLeds_Open();

	// Config and start of ADC
	mAd_Setup();
	mAd_Open();

	// Config and start of SPI
	mSpi_Setup();
	mSpi_Open();

	// Config and start non-blocking delay by PIT
	mDelay_Setup();
	mDelay_Open();

	// Timer Config for Speed Measurement and PWM Outputs for Servos
	mTimer_Setup();
	mTimer_Open();

//	// Setup FXOS8700CQ
//	mAccelMagneto_Setup();
//	mAccelMagneto_Open();

//	// Setup FXAS21002C
//	mGyro_Setup();
//	mGyro_Open();

	// Config and start of the DAC0 used to drive the driver LED lighting
	mDac_Setup();
	mDac_Open();

	// Setup and start of motor and servo PWM controls and speed measurement
	mTimer_Setup();
	mTimer_Open();

	// Enable IRQ at the CPU -> Primask
	__enable_irq();

	// UART 4 monitoring image
	mRs232_Setup();
	mRs232_Open();


//	int		VectCount = 0;

//	while (true)
//	{
//		pixy.line.getAllFeatures(LINE_VECTOR, true);
//		VectCount++;
//		if (mDelay_IsDelayDone(kPit1, DelayNumb))
//		{
//			VectCount = 0;
//			mDelay_ReStart(kPit1, DelayNumb, 100);
//		}
//	}


	Pixy2SPI_SS	pixy;
	pixy.init();
	pixy.setLamp(0, 0);

	while (true)
	{
		mTimer_SetMotorDuty(0, 0);
		mTimer_SetServoDuty(0, 0);

		// Ждем, поднятия переключателя, чтоб машина поехала
		while (!mSwitch_ReadSwitch(kSw1));

		// Запускает двигатель
		mTimer_SetMotorDuty(-0.5, 0.5);

		// Цикл работает, пока поднят переключатель
		while (mSwitch_ReadSwitch(kSw1))
		{
			gInput_Execute(pixy);
			if (gInput.chosen_count == 1)
				printf("{(x0 = %d, y0 = %d), (x1 = %d, y1 = %d)}\n", gInput.chosen_vectors[0].m_x0, gInput.chosen_vectors[0].m_y0,
						gInput.chosen_vectors[0].m_x1, gInput.chosen_vectors[0].m_y1);
			else
			{
				printf("{(x0 = %d, y0 = %d), (x1 = %d, y1 = %d)}, ", gInput.chosen_vectors[0].m_x0, gInput.chosen_vectors[0].m_y0,
						gInput.chosen_vectors[0].m_x1, gInput.chosen_vectors[0].m_y1);
				printf("{(x0 = %d, y0 = %d), (x1 = %d, y1 = %d)}\n", gInput.chosen_vectors[1].m_x0, gInput.chosen_vectors[1].m_y0,
						gInput.chosen_vectors[1].m_x1, gInput.chosen_vectors[1].m_y1);
			}
			gCompute_Execute();
			gOutput_Execute();
		}
	}


	return 0;
}
