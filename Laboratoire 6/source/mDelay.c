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
		iPit_InitDelay();
	}

bool mDelay_GetFlag(void)
	{
		return iPit_GetFlag();
	}

void mDelay_ResetFlag(void)
	{
		iPit_ResetFlag();
	}

int mDelay_GetDelay(unsigned int aDelay)
	{
		return iPit_GetDelay(aDelay);
	}

void mDelay_DelayRelease(unsigned int aDelayNo)
	{
		iPit_DelayRelease(aDelayNo);
	}

bool mDelay_IsDelayDone(unsigned int aDelayNo)
	{
		return iPit_IsDelayDone(aDelayNo);
	}
