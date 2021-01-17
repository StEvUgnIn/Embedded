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
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

enum GPIOx_PDDR
	{
	GPIOA_PDDR = 0x400FF014,
	GPIOB_PDDR = 0x000FF054,
	GPIOC_PDDR = 0x400FF094,
	GPIOD_PDDR = 0x400FF0D4
	};

enum GPIOx_PIDR
	{
	GPIOA_PIDR = 0x400FF010,
	GPIOB_PIDR = 0x000FF050,
	GPIOC_PIDR = 0x400FF090,
	GPIOD_PIDR = 0x400FF0D0
	};

enum GPIOx_PDOR
	{
	GPIOA_PDOR = 0x400FF000,
	GPIOB_PDOR = 0x400FF040,
	GPIOC_PDOR = 0x400FF080,
	GPIOD_PDOR = 0x400FF0C0
	};

/*
enum LED
	{
	LED1 = GPIOD_BASE & (1 << 2),
	LED2 = GPIOA_BASE & (1 << 13),
	LED3 = GPIOC_BASE & (1 << 9),
	LED4 = GPIOC_BASE & (1 << 8),
	LED5 = GPIOA_BASE & (1 << 5),
	LED6 = GPIOA_BASE & (1 << 4),
	LED7 = GPIOA_BASE & (1 << 12),
	LED8 = GPIOD_BASE & (1 << 3)
	};

enum SWITCH
	{
	SWITCH1 = GPIOB_BASE & (1 << 18),
	SWITCH2 = GPIOB_BASE & (1 << 19),
	SWITCH3 = GPIOC_BASE & (1 << 0),
	SWITCH4 = GPIOC_BASE & (1 << 4),
	SWITCH5 = GPIOC_BASE & (1 << 6),
	SWITCH6 = GPIOC_BASE & (1 << 7),
	SWITCH7 = GPIOC_BASE & (1 << 10),
	SWITCH8 = GPIOC_BASE & (1 << 11)
	};

enum PUSHBUT
	{
	PUSHBUT1 = GPIOD_BASE & (1 << 5),
	PUSHBUT2 = GPIOD_BASE & (1 << 7),
	PUSHBUT3 = GPIOD_BASE & (1 << 6),
	PUSHBUT4 = GPIOD_BASE & (1 << 4)
	};
	*/

// variable pointeur accès au registre des ports I/O
unsigned long *gPinCtrlAddr;
unsigned long *gPDDRAddr;

/*
 * @brief   Application entry point.
 */
void main(void)
	{
		// horloges des ports utilises
		unsigned long* SIM_SCGC5 = (unsigned long*) 0x40048038;
		*SIM_SCGC5 = (1 << 9) | (1 << 10) | (1 << 11) | (1 << 12);

		// @TODO ajouter la fonctionnalité de chaque pin

		// configuration des entrées et sorties
		gPinCtrlAddr = (unsigned long*) GPIOA_PDDR;
		*gPinCtrlAddr = (1 << 4) | (1 << 5) | (1 << 12) | (1 << 13);
		gPinCtrlAddr = (unsigned long*) GPIOB_PDDR;
		// *gPDDRAddr = 0 | *gPDDRAddr; // puting a zero value creates a hard fault error
		gPinCtrlAddr = (unsigned long*) GPIOC_PDDR;
		*gPinCtrlAddr = (1 << 8) | (1 << 9);
		gPinCtrlAddr = (unsigned long*) GPIOD_PDDR;
		*gPinCtrlAddr = (1 << 2) | (1 << 3);

		for (;;)
			{
				// on lit le PushBut1
				gPinCtrlAddr = (unsigned long*) (GPIOD_PIDR & (1 << 5));
				if (*gPinCtrlAddr)
					{
						// on éteint toutes les LEDs
						gPinCtrlAddr = (unsigned long*) GPIOA_PDOR;
						*gPDDRAddr &= ~((1 << 4) | (1 << 5) | (1 << 12) | (1 << 13));
						gPinCtrlAddr = (unsigned long*) GPIOB_PDOR;
						*gPDDRAddr &= 0;
						gPinCtrlAddr = (unsigned long*) GPIOC_PDOR;
						*gPDDRAddr &= ~((1 << 8) | (1 << 9));
						gPinCtrlAddr = (unsigned long*) GPIOD_PDOR;
						*gPDDRAddr &= ~((1 << 2) | (1 << 3));
					}
				else
					{
						// on lit le PushBut2
						gPinCtrlAddr = (unsigned long*) (GPIOD_PIDR & (1 << 5));
						if (*gPinCtrlAddr)
							{
								// on allume toutes les LEDs
								gPinCtrlAddr = (unsigned long*) GPIOA_PDOR;
								*gPDDRAddr |= (1 << 4) | (1 << 5) | (1 << 12) | (1 << 13);
								gPinCtrlAddr = (unsigned long*) GPIOB_PDOR;
								*gPDDRAddr |= 0;
								gPinCtrlAddr = (unsigned long*) GPIOC_PDOR;
								*gPDDRAddr |= (1 << 8) | (1 << 9);
								gPinCtrlAddr = (unsigned long*) GPIOD_PDOR;
								*gPDDRAddr |= (1 << 2) | (1 << 3);
							}
						else
							{
								// on lit le Switch 1
								gPinCtrlAddr = (unsigned long*) (GPIOB_PIDR & (1 << 18));
								if (*gPinCtrlAddr)
									{
										// on allume la LED 5
										gPinCtrlAddr = (unsigned long*) GPIOA_PDOR;
										*gPinCtrlAddr |= (1 << 5);
									}
								else
									{
										// on éteint la LED 5
										gPinCtrlAddr = (unsigned long*) GPIOA_PDOR;
										*gPinCtrlAddr &= ~(1 << 5);
									}

								// on lit le Switch 2
								gPinCtrlAddr = (unsigned long*) (GPIOB_PIDR & (1 << 19));
								if (*gPinCtrlAddr)
									{
										// on allume la LED 4
										gPinCtrlAddr = (unsigned long*) GPIOC_PDOR;
										*gPinCtrlAddr |= (1 << 8);
									}
								else
									{
										// on éteint la LED 4
										gPinCtrlAddr = (unsigned long*) GPIOC_PDOR;
										*gPinCtrlAddr &= ~(1 << 8);
									}
								// on lit le Switch 3
								gPinCtrlAddr = (unsigned long*) (GPIOC_PIDR & (1 << 0));
								if (*gPinCtrlAddr)
									{
										// on allume la LED 3
										gPinCtrlAddr = (unsigned long*) GPIOC_PDOR;
										*gPinCtrlAddr |= (1 << 9);
									}
								else
									{
										// on éteint la LED 3
										gPinCtrlAddr = (unsigned long*) GPIOC_PDOR;
										*gPinCtrlAddr &= ~(1 << 9);
									}

								// on lit le Switch 4
								gPinCtrlAddr = (unsigned long*) (GPIOC_PIDR & (1 << 4));
								if (*gPinCtrlAddr)
									{
										// on allume la LED 2
										gPinCtrlAddr = (unsigned long*) GPIOA_PDOR;
										*gPinCtrlAddr |= (1 << 13);
									}
								else
									{
										// on éteint la LED 2
										gPinCtrlAddr = (unsigned long*) GPIOA_PDOR;
										*gPinCtrlAddr &= ~(1 << 13);
									}

								// on lit le Switch 5
								gPinCtrlAddr = (unsigned long*) (GPIOC_PIDR & (1 << 6));
								if (*gPinCtrlAddr)
									{
										// on allume la LED 1
										gPinCtrlAddr = (unsigned long*) GPIOD_PDOR;
										*gPinCtrlAddr |= (1 << 2);
									}
								else
									{
										// on éteint la LED 1
										gPinCtrlAddr = (unsigned long*) GPIOD_PDOR;
										*gPinCtrlAddr &= ~(1 << 2);
									}

								// on lit le Switch 6
								gPinCtrlAddr = (unsigned long*) (GPIOC_PIDR & (1 << 7));
								if (*gPinCtrlAddr)
									{
										// on allume la LED 8
										gPinCtrlAddr = (unsigned long*) GPIOD_PDOR;
										*gPinCtrlAddr |= (1 << 3);
									}
								else
									{
										// on allume la LED 8
										gPinCtrlAddr = (unsigned long*) GPIOD_PDOR;
										*gPinCtrlAddr &= ~(1 << 3);
									}

								// on lit le Switch 7
								gPinCtrlAddr = (unsigned long*) (GPIOC_PIDR & (1 << 10));
								if (*gPinCtrlAddr)
									{
										// on allume la LED 7
										gPinCtrlAddr = (unsigned long*) GPIOA_PDOR;
										*gPinCtrlAddr |= (1 << 12);
									}
								else
									{
										// on éteint la LED 7
										gPinCtrlAddr = (unsigned long*) GPIOA_PDOR;
										*gPinCtrlAddr &= ~(1 << 12);
									}

								// on lit le Switch 8
								gPinCtrlAddr = (unsigned long*) (GPIOC_PIDR & (1 << 11));
								if (*gPinCtrlAddr)
									{
										// on allume la LED 6
										gPinCtrlAddr = (unsigned long*) GPIOA_PDOR;
										*gPinCtrlAddr |= (1 << 4);
									}
								else
									{
										// on éteint la LED 6
										gPinCtrlAddr = (unsigned long*) GPIOA_PDOR;
										*gPinCtrlAddr &= ~(1 << 4);
									}
							}
					}
			}
	}
