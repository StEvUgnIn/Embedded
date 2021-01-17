/*
 * iDio.c
 *
 *  Created on: 4 nov. 2019
 *      Author: steve.huguenin
 */

#include "iDio.h"

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
