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
		mLcd_Setup();
		EnableInterrupts; // bit PM de PRIMASK à 1
		mDelay_Setup();

		mLcd_Open();

		gInput_Setup();
		gCompute_Setup();
		gOutput_Setup();

		// Ecriture du message de base
		// mLcd_WriteEntireDisplay("Central Alarme  Alarme 0 OFF    ");

		// Boucle infinie
		for (;;)
			{
				gInput_Execute();
				gCompute_Execute();
				gOutput_Execute();
			}
	}
