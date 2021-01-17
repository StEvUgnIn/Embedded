/*
 ------------------------------------------------------------
 Copyright 2019-2020 Haute Ecole ARC Ingénierie,
 Switzerland. All rights reserved
 ------------------------------------------------------------
 Nom du fichier : gInput.c
 Auteur et Date : Steve Huguenin-Elie / 20.03.2020
 Description dans le fichier gInput.h
 ------------------------------------------------------------
 */

#include "gInput.h"
#include "gMBox.h"
#include "mSwitch.h"

void gInput_Setup(void)
	{
	}

void gInput_Execute(void)
	{
		for (SwitchEnum i = kSw1; i <= kSw8; i++) gInput.aSwTab[i] = mSwitch_ReadSwitch(i);
	}
