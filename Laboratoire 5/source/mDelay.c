/*
 ------------------------------------------------------------
 Copyright 2019-2020 Haute Ecole ARC Ingénierie,
 Switzerland. All rights reserved
 ------------------------------------------------------------
 Nom du fichier : mDelay.c
 Auteur et Date : Steve Huguenin-Elie / 11.11.2019
 Description dans le fichier mDelay.h
 ------------------------------------------------------------
 */

#include "mDelay.h"

#define kPit0Per 1
#define kPit1Per 10

void mDelay_Setup(unsigned long milliseconds)
	{
		iPit_Config(kPit0Per, kPit1Per);
		iPit_StartPit(kPIT0);
	}

bool mDelay_GetFlag(void)
	{
		return iPit_GetFlag();
	}

void mDelay_ResetFlag(void)
	{
		iPit_ResetFlag();
	}
