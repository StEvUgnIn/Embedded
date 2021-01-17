/*
 ------------------------------------------------------------
 Copyright 2019-2020 Haute Ecole ARC Ingénierie,
 Switzerland. All rights reserved
 ------------------------------------------------------------
 Nom du fichier : iUart.h
 Auteur et Date : steve.huguenin / 23 mars 2020
 But :
 Modifications

 ------------------------------------------------------------
 */
#ifndef IUART_H_
#define IUART_H_

#include "def.h"

void iUart_Config(void);

void iUart_EnDisTx(UInt8);

void iUart_EnDisRx(UInt8);

bool iUart_GetStatus(UInt8 aStatus);

UInt8 iUart_GetData(void);

void iUart_SetData(UInt8 aData);

bool iUart_IsBufferEmpty(void);

UChar iUart_GetCharFromBuffer(void);

#endif /* IUART_H_ */
