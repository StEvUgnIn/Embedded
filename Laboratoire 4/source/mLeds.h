/*
 * mLeds.h
 *
 *  Created on: 4 nov. 2019
 *      Author: steve.huguenin
 */

#ifndef MLEDS_H_
#define MLEDS_H_

#include "def.h"

// Setup
void mLeds_Setup(void);

// On Off des LED
void mLeds_Write(LedMaskEnum aMask, LedStateEnum aState);

#endif /* MLEDS_H_ */
