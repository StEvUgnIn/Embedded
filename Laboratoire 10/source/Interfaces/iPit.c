/*
 ------------------------------------------------------------
 Copyright 2019-2020 Haute Ecole ARC Ingénierie,
 Switzerland. All rights reserved
 ------------------------------------------------------------
 Nom du fichier : iPit.c
 Auteur et Date : Steve Huguenin-Elie / 11.11.2019
 Description dans le fichier iPit.h
 ------------------------------------------------------------
 */

#include "iPit.h"

#define kClockCpu	48
#define kClockBus	24

#define kNbOfDelay 10
struct DelayStruct
	{
		unsigned int Counter; // La valeur du delay désiré
		bool IsFree; // Le delay est déjà utilisé?
		bool IsDone; // Le delay est échu?
	};
static struct DelayStruct sDelayTab[kNbOfDelay];

static bool sPitFlag = false;

void iPit_Config(unsigned int aPIT0PeriodeMs, unsigned int aPIT1PeriodeMs)
	{
		unsigned long *aPitPtr;
		// activation du clock du PIT
		aPitPtr = (unsigned long *) kSIM_SCGC6;
		*aPitPtr |= 0x1 << 23;
		aPitPtr = (unsigned long *) kPIT_MCR;
		*aPitPtr &= 0xFFFD;
#ifdef DEBUG
		*aPitPtr |= 0x1;
#endif
		aPitPtr = (unsigned long *) kPIT_LDVAL0;
		*(aPitPtr) = aPIT0PeriodeMs * kClockBus * 1000;
		aPitPtr = (unsigned long *) kPIT_LDVAL1;
		*(aPitPtr) = aPIT1PeriodeMs * kClockBus * 1000;
		aPitPtr = (unsigned long *) kPIT_TCTRL0;
		*(aPitPtr) |= 0x2;
		aPitPtr = (unsigned long *) kPIT_TCTRL1;
		*(aPitPtr) |= 0x2;
		aPitPtr = (unsigned long *) kNVIC_ISER;
		*aPitPtr |= 0x1 << 22;
		aPitPtr = (unsigned long *) kNVIC_IPR5;
		*aPitPtr |= 0x3 << 22;
	}

void iPit_StartPit(PITEnum aPIT)
	{
		if ((kPIT0 & aPIT) == kPIT0)
			{
				unsigned long *aPitPtr = (unsigned long*) kPIT_TCTRL0;
				*(aPitPtr) |= 0x1;
			}

		if ((kPIT1 & aPIT) == kPIT1)
			{
				unsigned long *aPitPtr = (unsigned long*) kPIT_TCTRL1;
				*(aPitPtr) |= 0x1;
			}
	}

bool iPit_GetFlag(void)
	{
		return sPitFlag;
	}

void iPit_ResetFlag(void)
	{
		sPitFlag = false;
	}

void PIT_IRQHandler(void)
	{
		static unsigned long sCompteur = 0;
		unsigned long *aTlfg0Ptr = (unsigned long*) kPIT_TFLG0;
		unsigned long *aTlfg1Ptr = (unsigned long*) kPIT_TFLG1;

		if ((*aTlfg0Ptr & 0x1))
			{
				// Reset du flag
				*aTlfg0Ptr |= 0x1;

				sCompteur++;

				if (sCompteur >= 500)
					{
						sCompteur = 0;
						sPitFlag = true;
					}
			}

		if ((*aTlfg1Ptr & 0x1))
			{
				// Reset du flag
				*aTlfg1Ptr |= 0x1;

				// Rien pour l'instant
			}

		for (int i = 0; i < kNbOfDelay; ++i)
			{
				if (!sDelayTab[i].IsFree)
					{
						if (!sDelayTab[i].IsDone)
							{
								sDelayTab[i].Counter--;
								if (sDelayTab[i].Counter == 0)
									{
										sDelayTab[i].IsDone = true;
									}
							}
					}
			}
	}

void iPit_InitDelay(void)
	{
		for (unsigned int i = 0; i < kNbOfDelay; ++i)
			{
				iPit_DelayRelease(i);
			}
	}

int iPit_GetDelay(unsigned int aDelay)
	{
		for (unsigned int i = 0; i < kNbOfDelay; ++i)
			{
				if (sDelayTab[i].IsFree)
					{
						sDelayTab[i].IsFree = false;
						sDelayTab[i].Counter = aDelay;
						return i;
					}
			}
		return -1;
	}

void iPit_DelayRelease(unsigned int aDelayNo)
	{
		sDelayTab[aDelayNo].Counter = 0;
		sDelayTab[aDelayNo].IsDone = false;
		sDelayTab[aDelayNo].IsFree = true;
	}

bool iPit_IsDelayDone(unsigned int aDelayNo)
	{
		return sDelayTab[aDelayNo].IsDone;
	}
