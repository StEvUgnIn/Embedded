/*
 ------------------------------------------------------------
 Copyright 2019-2020 Haute Ecole ARC Ingénierie,
 Switzerland. All rights reserved
 ------------------------------------------------------------
 Nom du fichier : mLeds.c
 Auteur et Date : Steve Huguenin-Elie / 04.11.2019
 Description dans le fichier mLeds.h
 ------------------------------------------------------------
 */

#include "iDio.h"
#include "mLeds.h"

void mLeds_Setup(void)
	{
		iDio_EnablePortClk();
		iDio_PinConfig(kPortA, kPin4, kAlternate1);
		iDio_PinConfig(kPortA, kPin5, kAlternate1);
		iDio_PinConfig(kPortA, kPin12, kAlternate1);
		iDio_PinConfig(kPortA, kPin13, kAlternate1);
		iDio_PinConfig(kPortC, kPin8, kAlternate1);
		iDio_PinConfig(kPortC, kPin9, kAlternate1);
		iDio_PinConfig(kPortD, kPin2, kAlternate1);
		iDio_PinConfig(kPortD, kPin3, kAlternate1);
		iDio_SetPortDirection(kPortA, kMaskIo4 + kMaskIo5 + kMaskIo12 + kMaskIo13,
				kIoOutput);
		iDio_SetPortDirection(kPortC, kMaskIo8 + kMaskIo9, kIoOutput);
		iDio_SetPortDirection(kPortD, kMaskIo2 + kMaskIo3, kIoOutput);
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
