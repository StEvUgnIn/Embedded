/*
------------------------------------------------------------
Copyright 2019-2020 Haute Ecole ARC Ingénierie,
Switzerland. All rights reserved
------------------------------------------------------------
Nom du fichier : mLeds.h
Auteur et Date : Steve Huguenin-Elie / 11.11.2019
But :						 Allumage et Extinction des LEDs
Modifications

------------------------------------------------------------
*/

#ifndef MLEDS_H_
#define MLEDS_H_

#include "def.h"

// Setup
void mLeds_Setup(void);

// On Off des LED
void mLeds_Write(LedMaskEnum aMask, LedStateEnum aState);

#endif /* MLEDS_H_ */
