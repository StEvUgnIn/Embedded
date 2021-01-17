/*
 ------------------------------------------------------------
 Copyright 2019-2020 Haute Ecole ARC Ingénierie,
 Switzerland. All rights reserved
 ------------------------------------------------------------
 Nom du fichier : main.c
 Auteur et Date : Steve Huguenin-Elie / 11.11.2019
 Description dans le fichier main.h
 ------------------------------------------------------------
 */

#include "main.h"

//-----------------------------------------------------------------------------
// Programme principal
//-----------------------------------------------------------------------------
int main(void)
	{
		mCpu_Setup();
		mSwitch_Setup();
		mLeds_Setup();
		EnableInterrupts;
		mDelay_Setup(500); // période fixée à 500 ms

		LedMaskEnum aMask = kMaskLed1;

		// Boucle infinie
		for (;;)
			{
				if (mDelay_GetFlag()) // toutes les 500 ms
					{
						mDelay_ResetFlag();											// remet le flag à zero
						mLeds_Write(kMaskLedAll, kLedOff); 			// éteint toutes les LEDS

						switch (aMask)
							{
						case kMaskLed1:
							mLeds_Write(kMaskLed1, kLedOn);
							aMask = kMaskLed2;
							break;
						case kMaskLed2:
							mLeds_Write(kMaskLed2, kLedOn);
							aMask = kMaskLed3;
							break;
						case kMaskLed3:
							mLeds_Write(kMaskLed3, kLedOn);
							aMask = kMaskLed4;
							break;
						case kMaskLed4:
							mLeds_Write(kMaskLed4, kLedOn);
							aMask = kMaskLed5;
							break;
						case kMaskLed5:
							mLeds_Write(kMaskLed5, kLedOn);
							aMask = kMaskLed6;
							break;
						case kMaskLed6:
							mLeds_Write(kMaskLed6, kLedOn);
							aMask = kMaskLed7;
							break;
						case kMaskLed7:
							mLeds_Write(kMaskLed7, kLedOn);
							aMask = kMaskLed8;
							break;
						case kMaskLed8:
							mLeds_Write(kMaskLed8, kLedOn);
							aMask = kMaskLed1;
							break;
						default:
							aMask = kMaskLed1;
							}
					}
			} /* wait forever */
	}
