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

static EtatEnum sVarEtat;

//-----------------------------------------------------------------------------
// Programme principal
//-----------------------------------------------------------------------------
int main(void)
	{
		mCpu_Setup();
		mSwitch_Setup();
		mLeds_Setup();
		EnableInterrupts;
		mDelay_Setup(1); // période fixée à 1 ms

		unsigned int aDelayNo;

		// Boucle infinie
		for (;;)
			{
				if (mDelay_GetFlag()) // toutes les 1 ms
					{
						mDelay_ResetFlag();											// remet le flag à zero
						mLeds_Write(kMaskLedAll, kLedOff); 			// éteint toutes les LEDS

						switch (sVarEtat)
							{
						case kEtat1:
							mLeds_Write(kMaskLed1, kLedOn);
							if (mDelay_IsDelayDone(aDelayNo))
								{
									mDelay_DelayRelease(aDelayNo);
									aDelayNo = mDelay_GetDelay(200);
									sVarEtat = kEtat2;
								}
							break;
						case kEtat2:
							mLeds_Write(kMaskLed2, kLedOn);
							if (mDelay_IsDelayDone(aDelayNo))
								{
									mDelay_DelayRelease(aDelayNo);
									aDelayNo = mDelay_GetDelay(300);
									sVarEtat = kEtat3;
								}
							break;
						case kEtat3:
							mLeds_Write(kMaskLed3, kLedOn);
							sVarEtat = kEtat4;
							break;
						case kEtat4:
							mLeds_Write(kMaskLed4, kLedOn);
							sVarEtat = kEtat5;
							break;
						case kEtat5:
							mLeds_Write(kMaskLed5, kLedOn);
							sVarEtat = kEtat6;
							break;
						case kEtat6:
							mLeds_Write(kMaskLed6, kLedOn);
							sVarEtat = kEtat7;
							break;
						case kEtat7:
							mLeds_Write(kMaskLed7, kLedOn);
							sVarEtat = kEtat8;
							break;
						case kEtat8:
							mLeds_Write(kMaskLed8, kLedOn);
						default:
							if (mDelay_IsDelayDone(aDelayNo))
								{
									mDelay_DelayRelease(aDelayNo);
									aDelayNo = mDelay_GetDelay(100);
									sVarEtat = kEtat1;
								}
							}
					}
			} /* wait forever */
	}
