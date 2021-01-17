/*
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
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
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
 * @file    main.c
 * @brief   Application entry point.
 */
#include "MKL46Z4.h"
/* TODO: insert other include files here. */
#include "mSwitch.h"
#include "mLeds.h"
/* TODO: insert other definitions and declarations here. */

//-----------------------------------------------------------------------------
// Programme principal
//-----------------------------------------------------------------------------
int main(void)
	{
		mSwitch_Setup();
		mLeds_Setup();

		// Boucle infinie
		for (;;)
			{
				// Contrôle si le bouton PUSHBUT1 est "ON"
				if (mSwitch_ReadPushBut(kPushButSW1))
					{
						// On éteint toutes les LEDs
						mLeds_Write(kMaskLedAll, kLedOff);
					}
				// Contrôle si le bouton PUSHBUT2 est "ON"
				else if (mSwitch_ReadPushBut(kPushButSW2))
					{
						// On allume toutes les LEDS
						mLeds_Write(kMaskLedAll, kLedOn);
					}
				else
					{
						// Contrôle si l'interrupteur 1 est "ON"
						if (mSwitch_ReadSwitch(kSw1))
							{
								// On allume la LED 5
								mLeds_Write(kMaskLed5, kLedOn);
							}
						else
							{
								// On éteint la LED 5
								mLeds_Write(kMaskLed5, kLedOff);
							}

						// Contrôle si l'interrupteur 2 est "ON"
						if (mSwitch_ReadSwitch(kSw2))
							{
								// On allume la LED 6
								mLeds_Write(kMaskLed6, kLedOn);
							}
						else
							{
								// On éteint la LED 6
								mLeds_Write(kMaskLed6, kLedOff);
							}

						// Contrôle si l'interrupteur 3 est "ON"
						if (mSwitch_ReadSwitch(kSw3))
							{
								// On allume la LED 7
								mLeds_Write(kMaskLed7, kLedOn);
							}
						else
							{
								// On éteint la LED 7
								mLeds_Write(kMaskLed7, kLedOff);
							}

						// Contrôle si l'interrupteur 4 est "ON"
						if (mSwitch_ReadSwitch(kSw4))
							{
								// On allume la LED 8
								mLeds_Write(kMaskLed8, kLedOn);
							}
						else
							{
								// On éteint la LED 8
								mLeds_Write(kMaskLed8, kLedOff);
							}

						// Contrôle si l'interrupteur 5 est "ON"
						if (mSwitch_ReadSwitch(kSw5))
							{
								// On allume la LED 1
								mLeds_Write(kMaskLed1, kLedOn);
							}
						else
							{
								// On éteint la LED 1
								mLeds_Write(kMaskLed1, kLedOff);
							}

						// Contrôle si l'interrupteur 6 est "ON"
						if (mSwitch_ReadSwitch(kSw6))
							{
								// On allume la LED 2
								mLeds_Write(kMaskLed2, kLedOn);
							}
						else
							{
								// On éteint la LED 2
								mLeds_Write(kMaskLed2, kLedOff);
							}

						// Contrôle si l'interrupteur 7 est "ON"
						if (mSwitch_ReadSwitch(kSw7))
							{
								// On allume la LED 3
								mLeds_Write(kMaskLed3, kLedOn);
							}
						else
							{
								// On éteint la LED 3
								mLeds_Write(kMaskLed3, kLedOff);
							}

						// Contrôle si l'interrupteur 8 est "ON"
						if (mSwitch_ReadSwitch(kSw8))
							{
								// On allume la LED 4
								mLeds_Write(kMaskLed4, kLedOn);
							}
						else
							{
								// On éteint la LED 4
								mLeds_Write(kMaskLed4, kLedOff);
							}
					}
			} /* wait forever */
	}
