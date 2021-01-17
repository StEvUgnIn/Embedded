/*
 ------------------------------------------------------------
 Copyright 2019-2020 Haute Ecole ARC Ingénierie,
 Switzerland. All rights reserved
 ------------------------------------------------------------
 Nom du fichier : iPit.h
 Auteur et Date : Steve Huguenin-Elie / 11.11.2019
 But :						 Configuration du PIT
 Modifications

 ------------------------------------------------------------
 */

#ifndef IPIT_H_
#define IPIT_H_

#include "def.h"

#define kRTITime 1

void iPit_Config(unsigned int aPIT0PeriodeMs, unsigned int aPIT1PeriodeMs);

void iPit_StartPit(PITEnum aPIT);

bool iPit_GetFlag(void);

void iPit_ResetFlag(void);

void iPit_InitDelay(void);

int iPit_GetDelay(unsigned int aDelay);

void iPit_DelayRelease(unsigned int aDelayNo);

bool iPit_IsDelayDone(unsigned int aDelayNo);

#endif /* IPIT_H_ */
