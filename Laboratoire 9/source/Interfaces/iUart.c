/*
 ------------------------------------------------------------
 Copyright 2019-2020 Haute Ecole ARC Ingénierie,
 Switzerland. All rights reserved
 ------------------------------------------------------------
 Nom du fichier : iUart.c
 Auteur et Date : steve.huguenin / 23 mars 2020
 Description dans le fichier iUart.h
 ------------------------------------------------------------
 */

#include <MKL46Z4.h>
#include "iUart.h"

// Fréquence du bus
#define kBusClockkHz 24000
// Vitesse de transmission
#define kUart2BaudRate 115200

void iUart_Config(void)
	{
		// Enable du clock de l’UART2 (SIM->SCGC4)
		SIM->SCGC4 |= SIM_SCGC4_UART2_MASK;
		// crossbar pour les pins RX et TX, PTE16 et PTE17
		PORTE->PCR[16] |= PORT_PCR_MUX(3); // 0x200
		PORTE->PCR[17] |= PORT_PCR_MUX(3); // 0x200
		// Le format de la trame : 8 bits de données, 1 stop bit et pas de parité.
		UART2->C1 &= ~(0|(UART_C1_M_MASK|UART_C1_PE_MASK)); // 0xff
		// vitesse de transmission à 115200 bauds
#ifndef _LABO_9_CORRECTION_
		UART2->BDH &= ~UART_BDH_SBR_MASK; // 0x0
		UART2->BDL |= UART_BDL_SBR(0xD);  // 0xD
#else
		unsigned int aSbr = (unsigned int)((kBusClockkHz*1000)/(kUart2BaudRate * 16));
		UART2->BDH&=(~UART2->BDH);
		UART2->BDH|=UART_BDH_SBR(((aSbr & 0x1F00) >> 8));
		UART2->BDL= (unsigned char)(aSbr & UART_BDL_SBR_MASK);
#endif
		// Les interruptions : pas d’interruptions en réception et pas
		// d’interruptions en émission.
		UART2->C2 &= ~(0|(UART_C2_TIE_MASK|UART_C2_TCIE_MASK|UART_C2_RIE_MASK|UART_C2_ILIE_MASK)); // 0x0f;
		UART2->C3 &= ~(0|(UART_C3_ORIE_MASK|UART_C3_NEIE_MASK|UART_C3_FEIE_MASK|UART_C3_PEIE_MASK)); // 0xf0;
	}

void iUart_EnDisTx(uint8_t aRegisters)
	{
		if (aRegisters & UART_C2_TE_MASK)
			{
				UART2->C2 |= UART_C2_TE_MASK;
			}
		else if (aRegisters & ~UART_C2_TE_MASK)
			{
				UART2->C2 &= ~UART_C2_TE_MASK;
			}
	}

void iUart_EnDisRx(uint8_t aRegisters)
	{
		if (aRegisters & UART_C2_RE_MASK)
			{
				UART2->C2 |= UART_C2_RE_MASK;
			}
		else if (aRegisters & ~UART_C2_RE_MASK)
			{
				UART2->C2 &= ~UART_C2_RE_MASK;
			}
	}

bool iUart_GetStatus(UartStatusEnum aStatus)
	{
		return (UART2->S1 & aStatus & 0xff) == aStatus;
	}

uint8_t iUart_GetData(void)
	{
		return UART2->D;
	}

void iUart_SetData(uint8_t aData)
	{
		UART2->D = aData;
	}
