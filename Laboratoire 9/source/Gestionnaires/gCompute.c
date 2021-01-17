/*
 ------------------------------------------------------------
 Copyright 2019-2020 Haute Ecole ARC Ingénierie,
 Switzerland. All rights reserved
 ------------------------------------------------------------
 Nom du fichier : gCompute.c
 Auteur et Date : Steve Huguenin-Elie / 20.03.2020
 Description dans le fichier gCompute.h
 ------------------------------------------------------------
 */

#include <string.h>
#include "gCompute.h"
#include "gMBox.h"


void gCompute_Setup(void)
	{
	}

void gCompute_Execute(void)
	{
		memcpy(gCompute.aErrTab, gInput.aSwTab, sizeof gCompute.aErrTab);
	}
