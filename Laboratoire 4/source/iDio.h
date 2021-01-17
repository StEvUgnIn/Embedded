/*
 * iDio.h
 *
 *  Created on: 4 nov. 2019
 *      Author: steve.huguenin
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

#endif /* IDIO_H_ */
