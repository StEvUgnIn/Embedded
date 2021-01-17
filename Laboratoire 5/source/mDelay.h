/*
------------------------------------------------------------
Copyright 2019-2020 Haute Ecole ARC Ingénierie,
Switzerland. All rights reserved
------------------------------------------------------------
Nom du fichier : mDelay.h
Auteur et Date : Steve Huguenin-Elie / 18.11.2019
But :						 Configuration du module Delay
Modifications

------------------------------------------------------------
*/

#ifndef MDELAY_H_
#define MDELAY_H_

#include "iPit.h"

void mDelay_Setup(unsigned long milliseconds);

bool mDelay_GetFlag(void);

void mDelay_ResetFlag(void);

#endif /* MDELAY_H_ */
