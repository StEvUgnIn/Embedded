/*
------------------------------------------------------------
Copyright 2019-2020 Haute Ecole ARC Ingénierie,
Switzerland. All rights reserved
------------------------------------------------------------
Nom du fichier : iDio.c
Auteur et Date : Steve Huguenin-Elie / 11.11.2019
Description dans le fichier iDio.h
------------------------------------------------------------
*/

#include "iDio.h"
#include <MKL46Z4.h>

void iDio_EnablePortClk(void)
	{
		// Pointeur permettant d'accéder aux registres d'enable des clocks des port IO
		unsigned long *gSIMSCGC5Addr = (unsigned long*) 0x40048038;

		*gSIMSCGC5Addr = (0 | (1 << 9) | (1 << 10) | (1 << 11) | (1 << 12)
				| (1 << 13));
	}

void iDio_PinConfig(PortIOEnum aPort,PinNbEnum aPinNb, PinFunctionEnum aPinFunc)
{
	unsigned long *aPortPtr;

	// Configuration du pointeur selon le port pass� en param�tre
	switch(aPort)
		{
			case kPortA:
				aPortPtr=(unsigned long *)(kPORTA_PCR0+(aPinNb*4));
			break;
			case kPortB:
				aPortPtr=(unsigned long *)(kPORTB_PCR0+(aPinNb*4));
			break;
			case kPortC:
				aPortPtr=(unsigned long *)(kPORTC_PCR0+(aPinNb*4));
			break;
			case kPortD:
				aPortPtr=(unsigned long *)(kPORTD_PCR0+(aPinNb*4));
			break;
			case kPortE:
				aPortPtr=(unsigned long *)(kPORTE_PCR0+(aPinNb*4));
			break;
		}

	// Reset du champ MUX
	*aPortPtr&=0xFFFFF8FF;
	// Configuration de la fonction
	*aPortPtr|=aPinFunc;
}

void iDio_SetPortDirection(PortIOEnum aPort,IoMaskEnum aMask,IoDirectionEnum aDir)
{
  unsigned long *aPortPtr;

  // Configuration du pointeur selon le port pass� en param�tre
  switch(aPort)
    {
      case kPortA:
        aPortPtr=(unsigned long *)(kGPIOA_PDDR);
      break;
      case kPortB:
        aPortPtr=(unsigned long *)(kGPIOB_PDDR);
      break;
      case kPortC:
        aPortPtr=(unsigned long *)(kGPIOC_PDDR);
      break;
      case kPortD:
        aPortPtr=(unsigned long *)(kGPIOD_PDDR);
      break;
			case kPortE:
				aPortPtr=(unsigned long *)(kGPIOE_PDDR);
			break;
    }

  // Configuration des bits du port désiré en entrée ou sortie
  if(kIoOutput==aDir)
    {
      *aPortPtr |= aMask;
    }
  else if(kIoInput==aDir)
    {
      *aPortPtr &= ~aMask;
    }
}

void iDio_SetPort(PortIOEnum aPort, IoMaskEnum aMask, IoStateEnum aState)
	{
		unsigned long *aPortPtr;

		switch (aPort)
			{
		case kPortA:
			aPortPtr = (unsigned long*)(kGPIOA_PDOR);
			break;
		case kPortB:
			aPortPtr = (unsigned long*)(kGPIOB_PDOR);
			break;
		case kPortC:
			aPortPtr = (unsigned long*)(kGPIOC_PDOR);
			break;
		case kPortD:
			aPortPtr = (unsigned long*)(kGPIOD_PDOR);
			break;
		case kPortE:
			aPortPtr = (unsigned long*)(kGPIOE_PDOR);
			break;
			}

		// Configuration de l'état des bits du port configuré en sortie
		if (kIoOn == aState)
			{
				*aPortPtr |= aMask;
			}
		else if (kIoOff == aState)
			{
				*aPortPtr &= ~aMask;
			}
	}

bool iDio_GetPort(PortIOEnum aPort, IoMaskEnum aMask)
	{
		bool aRet = false;
		unsigned long *aPortPtr;

		switch (aPort)
			{
		case kPortA:
			aPortPtr = (unsigned long*)(kGPIOA_PDIR);
			break;
		case kPortB:
			aPortPtr = (unsigned long*)(kGPIOB_PDIR);
			break;
		case kPortC:
			aPortPtr = (unsigned long*)(kGPIOC_PDIR);
			break;
		case kPortD:
			aPortPtr = (unsigned long*)(kGPIOD_PDIR);
			break;
		case kPortE:
			aPortPtr = (unsigned long*)(kGPIOE_PDIR);
			break;
			}

		// Lecture de l'état des bit du port configuré en entrée
		aRet = (bool) ((*aPortPtr & aMask) == aMask);
		return aRet;
	}

void iDio_PortLcd(unsigned char aVal)
	// port E pin 21, 20 ,2 ,3 , 6, 18 et 19)
	{
		// Bit0, Bit1, Bit2, Bit3, Bit4, Bit5, Bit6, Bit7,
		// PTB20, PTE21, PTE20, PTE2, PTE3, PTE6, PTE18, PTE19,
		// Reset des bits du port E utilisés par le LCD
		GPIOE->PDOR &=(~(0|((kMaskIo2)|(kMaskIo3)|(kMaskIo6)|(kMaskIo18)|(kMaskIo19)|(kMaskIo20)|(kMaskIo21))));
		// Reset des bits du port B utilisés par le LCD
		GPIOB->PDOR &=(~(0|(kMaskIo20)));
		// Set des bits du port E utilisés par le LCD
		// Example: Data1 --> bit 21 du port E --> déplacement de 21-1 sur la gauche
		// Example: Data6 --> bit 18 du port E --> déplacement de 18-6 sur la gauche
		GPIOE->PDOR |=(((aVal&kMaskIo1)<<20)|((aVal&kMaskIo2)<<18)|((aVal&kMaskIo3)>>1)|
		((aVal&kMaskIo4)>>1)|((aVal&kMaskIo5)<<1)|((aVal&kMaskIo6)<<12)|((aVal&kMaskIo7)<<12));
		// Set des bits du port B utilisés par le LCD
		GPIOB->PDOR |=(((aVal&kMaskIo0)<<20));
	}
