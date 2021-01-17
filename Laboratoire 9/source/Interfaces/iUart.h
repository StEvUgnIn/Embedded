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

#include <def.h>

void iUart_Config(void);

void iUart_EnDisTx(uint8_t);

void iUart_EnDisRx(uint8_t);

bool iUart_GetStatus(uint8_t aStatus);

uint8_t iUart_GetData(void);

void iUart_SetData(uint8_t aData);

#endif /* IUART_H_ */
