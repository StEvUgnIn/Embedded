/*
 ------------------------------------------------------------
 Copyright 2019-2020 Haute Ecole ARC Ingénierie,
 Switzerland. All rights reserved
 ------------------------------------------------------------
 Nom du fichier : gTerminal.c
 Auteur et Date : steve.huguenin / 6 avr. 2020
 Description dans le fichier gTerminal.c.h
 ------------------------------------------------------------
 */

#include "gTerminal.h"
#include "gOutput.h"
#include "mRs232.h"

void gTerminal_Setup(void)
	{
		gOutput_Setup();
	}

void gTerminal_Execute(void)
	{
		gOutput_Execute();
	}
