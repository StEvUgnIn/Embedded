/*
 * mSwitch.h
 *
 *  Created on: 4 nov. 2019
 *      Author: steve.huguenin
 */

#ifndef MSWITCH_H_
#define MSWITCH_H_

#include <def.h>

void mSwitch_Setup(void);

// Lecture des interrupteurs
bool mSwitch_ReadSwitch(SwitchEnum aSwitchNb);

// Lecture des boutons poussoir
bool mSwitch_ReadPushBut(PushButEnum aPushButNb);

#endif /* MSWITCH_H_ */
