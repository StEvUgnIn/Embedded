/*
 ------------------------------------------------------------
 Copyright 2019-2020 Haute Ecole ARC Ingénierie,
 Switzerland. All rights reserved
 ------------------------------------------------------------
 Nom du fichier : mRs232.h
 Auteur et Date : steve.huguenin / 23 mars 2020
 But :
 Modifications

 ------------------------------------------------------------
 */
#ifndef MRS232_H_
#define MRS232_H_

#include "def.h"

void mRs232_Setup(void);

void mRs232_Open(void);

void mRs232_Close(void);

void mRs232_WriteChar(char);

void mRs232_WriteString(const char*);

#endif /* MRS232_H_ */
