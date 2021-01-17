/*
 ------------------------------------------------------------
 Copyright 2019-2020 Haute Ecole ARC Ingénierie,
 Switzerland. All rights reserved
 ------------------------------------------------------------
 Nom du fichier : mRs232.c
 Auteur et Date : steve.huguenin / 23 mars 2020
 Description dans le fichier mRs232.h
 ------------------------------------------------------------
 */

#include <MKL46Z4.h>
#include "mRs232.h"
#include "iUart.h"

void mRs232_Setup(void)
	{
		iUart_Config();
	}

void mRs232_Open(void)
	{
		iUart_EnDisRx(kEn);
		iUart_EnDisTx(kEn);
	}

void mRs232_Close(void)
	{
		iUart_EnDisRx(~(kEn) & 0xff);
		iUart_EnDisTx(~(kEn) & 0xff);
	}

void mRs232_WriteChar(char aData)
	{
		// fin de la transmission precedente
		while (0 == iUart_GetStatus(kTransmitComplete))
			;
		iUart_SetData(aData);
	}

void mRs232_WriteString(const char* aDataStr)
	{
		while ('\0' != *aDataStr)
			{
				mRs232_WriteChar(*aDataStr);
				aDataStr++;
			}
	}
