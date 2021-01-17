/*
 ------------------------------------------------------------
 Copyright 2019-2020 Haute Ecole ARC Ingénierie,
 Switzerland. All rights reserved
 ------------------------------------------------------------
 Nom du fichier : gMBox.h
 Auteur et Date : Steve Huguenin-Elie / 20.03.2020
 But :						 contient des structures de données (globales)
 Modifications

 ------------------------------------------------------------
 */

#ifndef GMBOX_H_
#define GMBOX_H_

#include "def.h"

#define kMaxLcdCarac ((unsigned char)(32))

// Création du type de la structure
typedef struct
	{
		bool aSwTab[8];
	} InputStruct;
// Exportation de la variable du type de la structure
extern InputStruct gInput;

// Création du type de la structure
typedef struct
	{
	// char theMessage[kMaxLcdCarac];
	// bool aLed1, aLed2, aLed3, aLed4, aLed5, aLed6, aLed7, aLed8, aLedAll;
	} OutputStruct;
// Exportation de la variable du type de la structure
extern OutputStruct gOutput;

// Création du type de la structure
typedef struct
	{
		bool aErrTab[8];
	} ComputeStruct;
// Exportation de la variable du type de la structure
extern ComputeStruct gCompute;

#endif /* GMBOX_H_ */
