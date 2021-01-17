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
		SwitchEnum i;
		LedMaskEnum j;

		mCpu_Setup();
		mSwitch_Setup();
		mLeds_Setup();
		mLcd_Setup();
		EnableInterrupts;
		// bit PM de PRIMASK à 1
		mDelay_Setup();

		mLcd_Open();

		// Ecriture du message de base
		mLcd_WriteEntireDisplay("Central Alarme  Alarme 0 OFF    ");

		// Boucle infinie
		for (;;)
			{
				// Lecture des interrupteurs et commande des LED
				for (i = kSw1, j = kMaskLed1; i <= kSw8; i++, j <<= 1)
					{
						// Lecture des interrupteurs
						sErrTab[i] = mSwitch_ReadSwitch(i);
						// affectation de l'état des interrupteurs aux LEDS
						if (true == sErrTab[i])
							{
								mLeds_Write(j, kLedOn);
							}
						else
							{
								mLeds_Write(j, kLedOff);
							}
					}
				// Affichage de l'état de chaque erreur
				switch (sAffState)
					{
				case kAffichage:
					// Affichage du message
					if (true == sErrTab[sAlarmNb])
						{
							mLcd_Write(sAlarmNb + 0x30, 7, 1);
							mLcd_Write('O', 9, 1);
							mLcd_Write('N', 10, 1);
							mLcd_Write(' ', 11, 1);
						}
					else
						{
							mLcd_Write(sAlarmNb + 0x30, 7, 1);
							mLcd_Write('O', 9, 1);
							mLcd_Write('F', 10, 1);
							mLcd_Write('F', 11, 1);
						}
					// Prise d'un delay
					sDelayLed = mDelay_GetDelay((unsigned int) kLedDelay);
					// prochain état
					sAffState = kWait1Sec;
					break;
				case kWait1Sec:
					// Si le delay est échu
					if (true == mDelay_IsDelayDone(sDelayLed))
						{
							// On relâche le delay
							mDelay_DelayRelease(sDelayLed);
							// Erreur suivante
							sAlarmNb++;
							// Saturation
							if (sAlarmNb > kSw8)
								{
									sAlarmNb = kSw1;
								}
							// Prochain état
							sAffState = kAffichage;
						}
					break;
					}
			}
	}
