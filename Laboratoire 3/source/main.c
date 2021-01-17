/*
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    main.c
 * @brief   Application entry point.
 */
#include "MKL46Z4.h"
/* TODO: insert other include files here. */
#include <stdbool.h>
/* TODO: insert other definitions and declarations here. */

//-------------------------------------------------------------------------
// Déclaration des constantes
//-------------------------------------------------------------------------
// Registres de direction
#define kGPIOA_PDDR     0x400FF014
#define kGPIOB_PDDR     0x400FF054
#define kGPIOC_PDDR     0x400FF094
#define kGPIOD_PDDR     0x400FF0D4
#define kGPIOE_PDDR     0x400FF114

// Registre de données --> sortie
#define kGPIOA_PDOR     0x400FF000
#define kGPIOB_PDOR     0x400FF040
#define kGPIOC_PDOR     0x400FF080
#define kGPIOD_PDOR     0x400FF0C0
#define kGPIOE_PDOR     0x400FF100

// Registre de données --> entrée
#define kGPIOA_PDIR     0x400FF010
#define kGPIOB_PDIR     0x400FF050
#define kGPIOC_PDIR     0x400FF090
#define kGPIOD_PDIR     0x400FF0D0
#define kGPIOE_PDIR     0x400FF110

// Registre permettant de configurer la fonctionnalité des pins
#define kPORTA_PCR0			0x40049000
#define kPORTB_PCR0			0x4004A000
#define kPORTC_PCR0			0x4004B000
#define kPORTD_PCR0			0x4004C000
#define kPORTE_PCR0			0x4004D000

// Direction des IO --> entrée ou sortie
typedef enum
	{
	kIoOutput, kIoInput
	} IoDirectionEnum;

// Masque des IO
typedef enum
	{
	kMaskIo0 = 0x01,
	kMaskIo1 = 0x02,
	kMaskIo2 = 0x04,
	kMaskIo3 = 0x08,
	kMaskIo4 = 0x10,
	kMaskIo5 = 0x20,
	kMaskIo6 = 0x40,
	kMaskIo7 = 0x80,
	kMaskIo8 = 0x100,
	kMaskIo9 = 0x200,
	kMaskIo10 = 0x400,
	kMaskIo11 = 0x800,
	kMaskIo12 = 0x1000,
	kMaskIo13 = 0x2000,
	kMaskIo14 = 0x4000,
	kMaskIo15 = 0x8000,
	kMaskIo16 = 0x10000,
	kMaskIo17 = 0x20000,
	kMaskIo18 = 0x40000,
	kMaskIo19 = 0x80000,
	kMaskIo20 = 0x100000,
	kMaskIo21 = 0x200000,
	kMaskIo22 = 0x400000,
	kMaskIo23 = 0x800000,
	kMaskIo24 = 0x1000000,
	kMaskIo25 = 0x2000000,
	kMaskIo26 = 0x4000000,
	kMaskIo27 = 0x8000000,
	kMaskIo28 = 0x10000000,
	kMaskIo29 = 0x20000000,
	kMaskIo30 = 0x40000000,
	kMaskIo31 = 0x80000000,
	kMaskIoAll = 0xffffffff
	} IoMaskEnum;

// Les différents port IO
typedef enum
	{
	kPortA, kPortB, kPortC, kPortD, kPortE
	} PortIOEnum;

// Etat des IO configurés en sortie
typedef enum
	{
	kIoOn, kIoOff
	} IoStateEnum;

// Fonctionnalité des pins
typedef enum
	{
	kAlternate0 = 0,
	kAlternate1 = 0x100,
	kAlternate2 = 0x200,
	kAlternate3 = 0x300,
	kAlternate4 = 0x400,
	kAlternate5 = 0x500,
	kAlternate6 = 0x600,
	kAlternate7 = 0x700
	} PinFunctionEnum;

// Numéro des PINS
typedef enum
	{
	kPin0 = 0,
	kPin1,
	kPin2,
	kPin3,
	kPin4,
	kPin5,
	kPin6,
	kPin7,
	kPin8,
	kPin9,
	kPin10,
	kPin11,
	kPin12,
	kPin13,
	kPin14,
	kPin15,
	kPin16,
	kPin17,
	kPin18,
	kPin19,
	kPin20,
	kPin21,
	kPin22,
	kPin23,
	kPin24,
	kPin25,
	kPin26,
	kPin27,
	kPin28,
	kPin29,
	kPin30,
	kPin31
	} PinNbEnum;

typedef enum
	{
	kMaskLed1 = 0x1,
	kMaskLed2 = 0x2,
	kMaskLed3 = 0x4,
	kMaskLed4 = 0x8,
	kMaskLed5 = 0x10,
	kMaskLed6 = 0x20,
	kMaskLed7 = 0x40,
	kMaskLed8 = 0x80,
	kMaskLedAll = 0xFF
	} LedMaskEnum;

typedef enum
	{
	kLedOff, kLedOn
	} LedStateEnum;

typedef enum
	{
	kSw1 = 0, kSw2 = 1, kSw3 = 2, kSw4 = 3, kSw5 = 4, kSw6 = 5, kSw7 = 6, kSw8 = 7
	} SwitchEnum;

typedef enum
	{
	kPushButSW1 = 0, kPushButSW2 = 1, kPushButSW3 = 2, kPushButSW4 = 3
	} PushButEnum;

//-----------------------------------------------------------------------------
// Déclaration des prototypes de fonctions
//-----------------------------------------------------------------------------

void iDio_EnablePortClk(void);

void iDio_PinConfig(PortIOEnum aPort, PinNbEnum aPinNb,
		PinFunctionEnum aPinFunc);

void iDio_SetPortDirection(PortIOEnum aPort, IoMaskEnum aMask,
		IoDirectionEnum aDir);

void iDio_SetPort(PortIOEnum aPort, IoMaskEnum aMask, IoStateEnum aState);

bool iDio_GetPort(PortIOEnum aPort, IoMaskEnum aMask);

// On Off des LED
void mLeds_Write(LedMaskEnum aMask, LedStateEnum aState);

// Lecture des interrupteurs
bool mSwitch_ReadSwitch(SwitchEnum aSwitchNb);

// Lecture des boutons poussoir
bool mSwitch_ReadPushBut(PushButEnum aPushButNb);

//-----------------------------------------------------------------------------
// Programme principal
//-----------------------------------------------------------------------------
int main(void)
	{

		// ------------------------------------------------------------
		// Enable du clock des ports IO
		// ------------------------------------------------------------
		iDio_EnablePortClk();

		// Configuration de la fonctionnalité de chaque PIN
		iDio_PinConfig(kPortA, kPin4, kAlternate1);
		iDio_PinConfig(kPortA, kPin5, kAlternate1);
		iDio_PinConfig(kPortA, kPin12, kAlternate1);
		iDio_PinConfig(kPortA, kPin13, kAlternate1);
		iDio_PinConfig(kPortB, kPin18, kAlternate1);
		iDio_PinConfig(kPortB, kPin19, kAlternate1);
		iDio_PinConfig(kPortC, kPin0, kAlternate1);
		iDio_PinConfig(kPortC, kPin4, kAlternate1);
		iDio_PinConfig(kPortC, kPin6, kAlternate1);
		iDio_PinConfig(kPortC, kPin7, kAlternate1);
		iDio_PinConfig(kPortC, kPin8, kAlternate1);
		iDio_PinConfig(kPortC, kPin9, kAlternate1);
		iDio_PinConfig(kPortC, kPin10, kAlternate1);
		iDio_PinConfig(kPortC, kPin11, kAlternate1);
		iDio_PinConfig(kPortD, kPin2, kAlternate1);
		iDio_PinConfig(kPortD, kPin3, kAlternate1);
		iDio_PinConfig(kPortD, kPin4, kAlternate1);
		iDio_PinConfig(kPortD, kPin5, kAlternate1);
		iDio_PinConfig(kPortD, kPin6, kAlternate1);
		iDio_PinConfig(kPortD, kPin7, kAlternate1);

		// Configuration des Ports en entrée ou en sortie
		iDio_SetPortDirection(kPortA, kMaskIo4 + kMaskIo5 + kMaskIo12 + kMaskIo13,
				kIoOutput);
		iDio_SetPortDirection(kPortB, kMaskIo18 + kMaskIo19, kIoInput);
		iDio_SetPortDirection(kPortC,
				kMaskIo0 + kMaskIo4 + kMaskIo6 + kMaskIo7 + kMaskIo10 + kMaskIo11,
				kIoInput);
		iDio_SetPortDirection(kPortC, kMaskIo8 + kMaskIo9, kIoOutput);
		iDio_SetPortDirection(kPortD, kMaskIo2 + kMaskIo3, kIoOutput);
		iDio_SetPortDirection(kPortD, kMaskIo4 + kMaskIo5 + kMaskIo6 + kMaskIo7,
				kIoInput);

		// Boucle infinie
		for (;;)
			{
				// Contrôle si le bouton PUSHBUT1 est "ON"
				if (mSwitch_ReadPushBut(kPushButSW1))
					{
						// On éteint toutes les LEDs
						mLeds_Write(kMaskLedAll, kLedOff);
					}
				// Contrôle si le bouton PUSHBUT2 est "ON"
				else if (mSwitch_ReadPushBut(kPushButSW2))
					{
						// On allume toutes les LEDS
						mLeds_Write(kMaskLedAll, kLedOn);
					}
				else
					{
						// Contrôle si l'interrupteur 1 est "ON"
						if (mSwitch_ReadSwitch(kSw1))
							{
								// On allume la LED 5
								mLeds_Write(kMaskLed5, kLedOn);
							}
						else
							{
								// On éteint la LED 5
								mLeds_Write(kMaskLed5, kLedOff);
							}

						// Contrôle si l'interrupteur 2 est "ON"
						if (mSwitch_ReadSwitch(kSw2))
							{
								// On allume la LED 6
								mLeds_Write(kMaskLed6, kLedOn);
							}
						else
							{
								// On éteint la LED 6
								mLeds_Write(kMaskLed6, kLedOff);
							}

						// Contrôle si l'interrupteur 3 est "ON"
						if (mSwitch_ReadSwitch(kSw3))
							{
								// On allume la LED 7
								mLeds_Write(kMaskLed7, kLedOn);
							}
						else
							{
								// On éteint la LED 7
								mLeds_Write(kMaskLed7, kLedOff);
							}

						// Contrôle si l'interrupteur 4 est "ON"
						if (mSwitch_ReadSwitch(kSw4))
							{
								// On allume la LED 8
								mLeds_Write(kMaskLed8, kLedOn);
							}
						else
							{
								// On éteint la LED 8
								mLeds_Write(kMaskLed8, kLedOff);
							}

						// Contrôle si l'interrupteur 5 est "ON"
						if (mSwitch_ReadSwitch(kSw5))
							{
								// On allume la LED 1
								mLeds_Write(kMaskLed1, kLedOn);
							}
						else
							{
								// On éteint la LED 1
								mLeds_Write(kMaskLed1, kLedOff);
							}

						// Contrôle si l'interrupteur 6 est "ON"
						if (mSwitch_ReadSwitch(kSw6))
							{
								// On allume la LED 2
								mLeds_Write(kMaskLed2, kLedOn);
							}
						else
							{
								// On éteint la LED 2
								mLeds_Write(kMaskLed2, kLedOff);
							}

						// Contrôle si l'interrupteur 7 est "ON"
						if (mSwitch_ReadSwitch(kSw7))
							{
								// On allume la LED 3
								mLeds_Write(kMaskLed3, kLedOn);
							}
						else
							{
								// On éteint la LED 3
								mLeds_Write(kMaskLed3, kLedOff);
							}

						// Contrôle si l'interrupteur 8 est "ON"
						if (mSwitch_ReadSwitch(kSw8))
							{
								// On allume la LED 4
								mLeds_Write(kMaskLed4, kLedOn);
							}
						else
							{
								// On éteint la LED 4
								mLeds_Write(kMaskLed4, kLedOff);
							}

					}

			} /* wait forever */
	}

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
			// DDRA
			case kPortA:
				aPortPtr=(unsigned long *)(kPORTA_PCR0+(aPinNb*4));

			break;

			// DDRB
			case kPortB:
				aPortPtr=(unsigned long *)(kPORTB_PCR0+(aPinNb*4));
			break;

			// DDRC
			case kPortC:
				aPortPtr=(unsigned long *)(kPORTC_PCR0+(aPinNb*4));
			break;

			// DDRD
			case kPortD:
				aPortPtr=(unsigned long *)(kPORTD_PCR0+(aPinNb*4));
			break;

			// DDRE
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
      // DDRA
      case kPortA:
        aPortPtr=(unsigned long *)(kGPIOA_PDDR);
      break;

      // DDRB
      case kPortB:
        aPortPtr=(unsigned long *)(kGPIOB_PDDR);
      break;

      // DDRC
      case kPortC:
        aPortPtr=(unsigned long *)(kGPIOC_PDDR);
      break;

      // DDRD
      case kPortD:
        aPortPtr=(unsigned long *)(kGPIOD_PDDR);
      break;

      // DDRE
       case kPortE:
         aPortPtr=(unsigned long *)(kGPIOE_PDDR);
       break;
    }

  // Configuration des bits du port d�sir� en entr�e ou sortie
  if(kIoOutput==aDir)
    {
      *aPortPtr|=aMask;
    }
  else if(kIoInput==aDir)
    {
      *aPortPtr &=~aMask;
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

void mLeds_Write(LedMaskEnum aMask, LedStateEnum aState)
//LED1 = PTD2
//LED2 = PTA13
//LED3 = PTC9
//LED4 = PTC8
//LED5 = PTA5
//LED6 = PTA4
//LED7 = PTA12
//LED8 = PTD3
	{
		if (kLedOn == aState)
			{
				iDio_SetPort(kPortA,
						((aMask & kMaskLed6) >> 1) | ((aMask & kMaskLed5) << 1)
								| ((aMask & kMaskLed7) << 6) | ((aMask & kMaskLed2) << 12),
						kIoOn);
				iDio_SetPort(kPortC,
						((aMask & kMaskLed4) << 5) | ((aMask & kMaskLed3) << 7), kIoOn);
				iDio_SetPort(kPortD,
						((aMask & kMaskLed1) << 2) | ((aMask & kMaskLed8) >> 4), kIoOn);
			}
		else if (kLedOff == aState)
			{
				iDio_SetPort(kPortA,
						((aMask & kMaskLed6) >> 1) | ((aMask & kMaskLed5) << 1)
								| ((aMask & kMaskLed7) << 6) | ((aMask & kMaskLed2) << 12),
						kIoOff);
				iDio_SetPort(kPortC,
						((aMask & kMaskLed4) << 5) | ((aMask & kMaskLed3) << 7), kIoOff);
				iDio_SetPort(kPortD,
						((aMask & kMaskLed1) << 2) | ((aMask & kMaskLed8) >> 4), kIoOff);
			}
	}

bool mSwitch_ReadSwitch(SwitchEnum aSwitchNb)
//SWITCH1 = PTB18
//SWITCH2 = PTB19
//SWITCH3 = PTC0
//SWITCH4 = PTC4
//SWITCH5 = PTC6
//SWITCH6 = PTC7
//SWITCH7 = PTC10
//SWITCH8 = PTC11
	{
		bool aState = false;

		switch (aSwitchNb)
			{
		case kSw1:
			aState = iDio_GetPort(kPortB, kMaskIo18);
			break;
		case kSw2:
			aState = iDio_GetPort(kPortB, kMaskIo19);
			break;
		case kSw3:
			aState = iDio_GetPort(kPortC, kMaskIo0);
			break;
		case kSw4:
			aState = iDio_GetPort(kPortC, kMaskIo4);
			break;
		case kSw5:
			aState = iDio_GetPort(kPortC, kMaskIo6);
			break;
		case kSw6:
			aState = iDio_GetPort(kPortC, kMaskIo7);
			break;
		case kSw7:
			aState = iDio_GetPort(kPortC, kMaskIo10);
			break;
		case kSw8:
			aState = iDio_GetPort(kPortC, kMaskIo11);
			break;
			}
		return aState;
	}

bool mSwitch_ReadPushBut(PushButEnum aPushButNb)
//	PUSHBUT1 = PTD5
//	PUSHBUT2 = PTD7
//	PUSHBUT3 = PTD6
//	PUSHBUT4 = PTD4
	{
		bool aState = false;

		switch (aPushButNb)
			{
		case kPushButSW1:
			aState = iDio_GetPort(kPortD, kMaskIo5);
			break;
		case kPushButSW2:
			aState = iDio_GetPort(kPortD, kMaskIo7);
			break;
		case kPushButSW3:
			aState = iDio_GetPort(kPortD, kMaskIo6);
			break;
		case kPushButSW4:
			aState = iDio_GetPort(kPortD, kMaskIo4);
			break;
			}

		return aState;
	}
