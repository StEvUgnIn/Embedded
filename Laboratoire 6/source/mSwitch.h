/*
------------------------------------------------------------
Copyright 2019-2020 Haute Ecole ARC Ingénierie,
Switzerland. All rights reserved
------------------------------------------------------------
Nom du fichier : def.h
Auteur et Date : Steve Huguenin-Elie / 11.11.2019
But :						 Configuration et Lecture des Switches
								 et des PushButtons
Modifications

------------------------------------------------------------
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
