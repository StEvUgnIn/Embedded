/*
------------------------------------------------------------
Copyright 2019-2020 Haute Ecole ARC Ingénierie,
Switzerland. All rights reserved
------------------------------------------------------------
Nom du fichier : iDio.h
Auteur et Date : Steve Huguenin-Elie / 11.11.2019
But :						 Gestion des I/O
Modifications

------------------------------------------------------------
*/

#ifndef IDIO_H_
#define IDIO_H_

#include "def.h"

void iDio_EnablePortClk(void);

void iDio_PinConfig(PortIOEnum aPort, PinNbEnum aPinNb,
		PinFunctionEnum aPinFunc);

void iDio_SetPortDirection(PortIOEnum aPort, IoMaskEnum aMask,
		IoDirectionEnum aDir);

void iDio_SetPort(PortIOEnum aPort, IoMaskEnum aMask, IoStateEnum aState);

bool iDio_GetPort(PortIOEnum aPort, IoMaskEnum aMask);

void iDio_PortLcd(unsigned char aVal);

#endif /* IDIO_H_ */
