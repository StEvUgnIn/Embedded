/*
 ------------------------------------------------------------
 Copyright 2019-2020 Haute Ecole ARC Ingénierie,
 Switzerland. All rights reserved
 ------------------------------------------------------------
 Nom du fichier : gOutput.c
 Auteur et Date : Steve Huguenin-Elie / 20.03.2020
 Description dans le fichier gOutput.h
 ------------------------------------------------------------
 */

#include <string.h>
#include "gOutput.h"
#include "gMBox.h"
#include "mSwitch.h"
#include "mLeds.h"
#include "mDelay.h"
#include "mLcd.h"

//-------------------------------------------------------------------------
// Déclaration des constantes
//-------------------------------------------------------------------------
// Les temps d'attente pour chaque LED
#define kLedDelay (1000/1.0)
//-------------------------------------------------------------------------
// Déclaration des variables globales
//-------------------------------------------------------------------------
// Enumération des états possible de la machine d'état
typedef enum
	{
	kAffichage, kWait1Sec
	} AffStateMachineEnum;
// Variable de la machine d'état de l'affichage
static AffStateMachineEnum sAffState = kAffichage;
// Nu du Delay de chaque LED
static int sDelayLed = 0;
// Compteur utilisé pour afficher l'état de chaque erreur
unsigned int sAlarmNb = kSw1;

SwitchEnum i;
LedMaskEnum j;

void gOutput_Setup(void)
	{
		// Ecriture du message de base
		mLcd_WriteEntireDisplay("Central Alarme  Alarme 0 OFF    ");
	}

void gOutput_Execute(void)
	{
		// commande des LED
		for (i = kSw1, j = kMaskLed1; i <= kSw8; i++, j <<= 1)
			{
				// affectation de l'état des interrupteurs aux LEDS
				if (true == gCompute.aErrTab[i])
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
			if (true == gCompute.aErrTab[sAlarmNb])
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

