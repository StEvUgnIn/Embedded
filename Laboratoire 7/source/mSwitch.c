/*
 * mSwitch.c
 *
 *  Created on: 4 nov. 2019
 *      Author: steve.huguenin
 */

#include "mSwitch.h"
#include "iDio.h"

void mSwitch_Setup(void)
	{
		iDio_EnablePortClk();
		iDio_PinConfig(kPortB, kPin18, kAlternate1);
		iDio_PinConfig(kPortB, kPin19, kAlternate1);
		iDio_PinConfig(kPortC, kPin0, kAlternate1);
		iDio_PinConfig(kPortC, kPin4, kAlternate1);
		iDio_PinConfig(kPortC, kPin6, kAlternate1);
		iDio_PinConfig(kPortC, kPin7, kAlternate1);
		iDio_PinConfig(kPortC, kPin10, kAlternate1);
		iDio_PinConfig(kPortC, kPin11, kAlternate1);
		iDio_PinConfig(kPortD, kPin7, kAlternate1);
		iDio_PinConfig(kPortD, kPin6, kAlternate1);
		iDio_PinConfig(kPortD, kPin5, kAlternate1);
		iDio_PinConfig(kPortD, kPin4, kAlternate1);
		iDio_SetPortDirection(kPortB, kMaskIo18 + kMaskIo19, kIoInput);
		iDio_SetPortDirection(kPortC,
				kMaskIo0 + kMaskIo4 + kMaskIo6 + kMaskIo7 + kMaskIo10 + kMaskIo11,
				kIoInput);
		iDio_SetPortDirection(kPortD, kMaskIo7 + kMaskIo6 + kMaskIo5 + kMaskIo4,
				kIoInput);
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

