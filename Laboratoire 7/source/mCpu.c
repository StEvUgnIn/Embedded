/*
------------------------------------------------------------
Copyright 2019-2020 Haute Ecole ARC Ingénierie,
Switzerland. All rights reserved
------------------------------------------------------------
Nom du fichier : mCpu.c
Auteur et Date : Steve Huguenin-Elie / 11.11.2019
Description dans le fichier mCpu.h
------------------------------------------------------------
*/
#include "mCpu.h"
#include "iCpu.h"

void mCpu_Setup(void)
	{
		iCpu_CLKInit();
	}
