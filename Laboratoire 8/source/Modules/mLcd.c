/*
 ------------------------------------------------------------
 Copyright 2019-2020 Haute Ecole ARC Ingénierie,
 Switzerland. All rights reserved
 ------------------------------------------------------------
 Nom du fichier : mLcd.c
 Auteur et Date : Steve Huguenin-Elie / 06.01.2020
 Description dans le fichier mLcd.h
 ------------------------------------------------------------
 */

#ifndef MLCD_H_
#define MLCD_H_

#include "iDio.h"
#include "iPit.h"
#include "mLcd.h"

// Nb de caractère max du lcd, ici 2 lignes de 16 caractères
#define kMaxLcdCarac ((unsigned char)(32))
// Nb de ligne
#define kNbOfLine ((unsigned char)(2))
// Nb de caractères par ligne
#define kNbOfChar ((unsigned char)(16))
// Définition des commandes LCD --> data 0 à data 7
// Efface le display et address counter=0
#define kClearDisplay ((unsigned char)(0x01))
// Address counter=0
#define kReturnHome ((unsigned char)(0x02))
// Lcd en mode 2 lignes,bus de 8 bits
#define k8BitsMode_2Lines ((unsigned char)(0x38))
// Enclenche le display sans le curseur
#define kDisplayOnNoCursor ((unsigned char)(0x0c))
// Enclenche le display avec le curseur qui clignote
#define kDisplayOnWithCursorBlink ((unsigned char)(0x0f))
// Eteint l'écran
#define kDisplayOff ((unsigned char)(0x08))
// Déplacement du curseur vers la droite
#define kMoveCursorRight ((unsigned char)(0x14))
// Déplacement du curseur vers la gauche
#define kMoveCursorLeft ((unsigned char)(0x10))
// Début de la ligne 2
#define kLineJump ((unsigned char)(0xc0))
// Mode incrément, pas de shift écran
#define kIncrModeShiftOff ((unsigned char)(0x06))
// Set DDRAM address
#define kSetDDRAMAdr ((unsigned char)(0x80))
// Init value
#define kInitValue ((unsigned char)(0x30))

static void mLcd_SendLcdCmd(unsigned char aCmd);
static void mLcd_SendLcdData(unsigned char aData);
static bool mLcd_ReadLcdBusy(void);

void mLcd_Setup(void)
	{
		// Configuration des fonctionnalités de chaque pin
		iDio_PinConfig(kPortB, kPin9, kAlternate1);
		iDio_PinConfig(kPortC, kPin16, kAlternate1);
		iDio_PinConfig(kPortC, kPin13, kAlternate1);
		iDio_PinConfig(kPortE, kPin2, kAlternate1);
		iDio_PinConfig(kPortE, kPin3, kAlternate1);
		iDio_PinConfig(kPortE, kPin6, kAlternate1);
		iDio_PinConfig(kPortE, kPin18, kAlternate1);
		iDio_PinConfig(kPortE, kPin19, kAlternate1);
		iDio_PinConfig(kPortE, kPin20, kAlternate1);
		iDio_PinConfig(kPortE, kPin21, kAlternate1);
		iDio_PinConfig(kPortB, kPin20, kAlternate1);

		// Configuration du Port C, RS et RW
		iDio_SetPortDirection(kPortC,kMaskIo13+kMaskIo16,kIoOutput);
		// Configuration du Port B, E et data0
		iDio_SetPortDirection(kPortB,kMaskIo9+kMaskIo20,kIoOutput);
		// Configuration du PortE, datas 1...7
		iDio_SetPortDirection(kPortE,kMaskIo2+kMaskIo3+kMaskIo6+kMaskIo18+kMaskIo19+kMaskIo20+kMaskIo21,kIoOutput);
	}

void mLcd_Open(void)
	{
		char aDelayNb=0;
		// Delay suivant la mise sous tension de 15 ms
		aDelayNb=iPit_GetDelay(15/kRTITime);
		while(!iPit_IsDelayDone(aDelayNb));
		iPit_DelayRelease(aDelayNb);
		// Envoi de la commande function set
		mLcd_SendLcdCmd(kInitValue);
		// Attente active de 4.1ms
		aDelayNb=iPit_GetDelay(5/kRTITime);
		while(!iPit_IsDelayDone(aDelayNb));
		iPit_DelayRelease(aDelayNb);
		// Envoi de la commande function set
		mLcd_SendLcdCmd(kInitValue);
		// Attente active de 100 us (min possible 1 ms)
		aDelayNb=iPit_GetDelay(kRTITime/kRTITime);
		while(!iPit_IsDelayDone(aDelayNb));
		iPit_DelayRelease(aDelayNb);
		// Envoi de la commande function set
		mLcd_SendLcdCmd(kInitValue);
		// ----------------------------------------
		// A partir d'ci on peut utiliser le busy
		// ----------------------------------------
		// Envoi de la commande function set: 2 lignes, interface 8 bits
		while(true==mLcd_ReadLcdBusy());
		mLcd_SendLcdCmd(k8BitsMode_2Lines);
		// Display OFF
		while(true==mLcd_ReadLcdBusy());
		mLcd_SendLcdCmd(kDisplayOff);
		// Efface l'écran
		while(true==mLcd_ReadLcdBusy());
		mLcd_SendLcdCmd(kClearDisplay);
		// Entry Mode set, mode incrément pas de shift écran
		while(true==mLcd_ReadLcdBusy());
		mLcd_SendLcdCmd(kIncrModeShiftOff);
		// Display ON, pas de curseur
		while(true==mLcd_ReadLcdBusy());
		mLcd_SendLcdCmd(kDisplayOnNoCursor);
	}

void mLcd_WriteEntireDisplay(const char *aChar)
	{
		unsigned int i;
		// Attente du busy flag=0
		while (true == mLcd_ReadLcdBusy())
			;
		// AC à 0, début de la 1ère ligne
		mLcd_SendLcdCmd(kReturnHome);
		// Envoi des 32 caractères à l'affichage
		// Attention il faut position manuellement l'Address Counter
		// au début de la 2e ligne lors de l'écriture de cette dernière
		for (i = 0; i < kMaxLcdCarac; i++)
			{
				// Attente du busy=0
				while (true == mLcd_ReadLcdBusy())
					;
				// Envoi du caractère au LCD
				mLcd_SendLcdData(*aChar);
				// Si fin de 1ère ligne on passe à la 2e
				if ((kNbOfChar-1) == i)
					{
						// Attente du busy flag=0
						while(true==mLcd_ReadLcdBusy());
						// 2e ligne
						mLcd_SendLcdCmd(kLineJump);
					}
				// Caractère suivant
				aChar++;
			}
	}

void mLcd_Write(unsigned char aChar, unsigned char aXpos, unsigned char aYpos)
	{
		unsigned int aTmp = 0;

		// Modification de l'Address Counter AC
		// Calcul de l'adresse DDRAM
		aTmp = (kSetDDRAMAdr) + aXpos + (aYpos*0x40);
		// Attente du busy flag=0
		while (true == mLcd_ReadLcdBusy())
			;
		// Set DDRAM Address Counter
		mLcd_SendLcdCmd(aTmp);
		// Attente du busy flag=0
		while (true == mLcd_ReadLcdBusy())
			;
		// Envoi du caractère au LCD
		mLcd_SendLcdData(aChar);
	}

void mLcd_SendLcdCmd(unsigned char aCmd)
	{
		iDio_SetPort(kPortB, kMaskIo9, kIoOff);
		iDio_SetPort(kPortC, kMaskIo13, kIoOff);
		iDio_SetPort(kPortC, kMaskIo16, kIoOff);

		iDio_PortLcd(aCmd);

		iDio_SetPort(kPortB, kMaskIo9, kIoOn);
		iDio_SetPort(kPortB, kMaskIo9, kIoOff);
	}

void mLcd_SendLcdData(unsigned char aData)
	{
		iDio_SetPort(kPortB, kMaskIo9, kIoOff);
		iDio_SetPort(kPortC, kMaskIo13, kIoOn);
		iDio_SetPort(kPortC, kMaskIo16, kIoOff);

		iDio_PortLcd(aData);

		iDio_SetPort(kPortB, kMaskIo9, kIoOn);
		iDio_SetPort(kPortB, kMaskIo9, kIoOff);
	}

bool mLcd_ReadLcdBusy(void)
	{
		bool aVal;

		// D0 à D7 en entrées
		iDio_SetPortDirection(kPortB,kMaskIo20,kIoInput);
		iDio_SetPortDirection(kPortE,kMaskIo2+kMaskIo3+kMaskIo6+kMaskIo18+kMaskIo19+kMaskIo20+kMaskIo21,kIoInput);

		iDio_SetPort(kPortB, kMaskIo9, kIoOff);
		iDio_SetPort(kPortC, kMaskIo13, kIoOff);
		iDio_SetPort(kPortC, kMaskIo16, kIoOn);
		iDio_SetPort(kPortB, kMaskIo9, kIoOn);

		aVal = iDio_GetPort(kPortE, kMaskIo19);
		iDio_SetPort(kPortB, kMaskIo9, kIoOff);

		// D0 à D7 en sorties
		iDio_SetPortDirection(kPortB,kMaskIo20,kIoOutput);
		iDio_SetPortDirection(kPortE,kMaskIo2+kMaskIo3+kMaskIo6+kMaskIo18+kMaskIo19+kMaskIo20+kMaskIo21,kIoOutput);

		iDio_SetPort(kPortB, kMaskIo9, kIoOn);
		iDio_SetPort(kPortB, kMaskIo9, kIoOff);

		return aVal;
	}

#endif /* MLCD_H_ */
