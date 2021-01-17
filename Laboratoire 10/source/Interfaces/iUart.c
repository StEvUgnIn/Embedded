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
#include <core_cm0plus.h>
#include "iUart.h"

// Buffer de 200 caractères
#define kUartRxBufSize ((UInt8)200)

//structure contenant le
// buffer, les index IN et OUT et le flag indiquant que le buffer est plein.
static struct UartRxBufStruct {
		UInt8 RxBuf[kUartRxBufSize];
		UInt16 InIndex;
		UInt16 OutIndex;
		UInt16 ByteCount;
		bool BufferIsFull;
}
sUartRxBufStruct;

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
		UART2->BDH &= ~UART_BDH_SBR_MASK; // 0x0
		UART2->BDL |= UART_BDL_SBR(0xD);  // 0xD
		// Les interruptions : interruption en réception et pas d’interruption en émission.
		UART2->C2 &= (~(0|(UART_C2_TIE_MASK|UART_C2_TCIE_MASK|UART_C2_ILIE_MASK))|UART_C2_RIE_MASK); // 0x0f;
		UART2->C3 &= (~(0|(UART_C3_ORIE_MASK|UART_C3_NEIE_MASK|UART_C3_FEIE_MASK|UART_C3_PEIE_MASK))); // 0xf0;
	}

void iUart_EnDisTx(UInt8 aRegisters)
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

void iUart_EnDisRx(UInt8 aRegisters)
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

void iUart_INTRx(void)
	{
		NVIC_EnableIRQ(UART2_IRQn);
		NVIC_SetPriority(UART2_IRQn, 2);
		// remettre le flag RDRF à 0
		while (true == UART2->S1);
		while (UART2->D);
	}

bool iUart_GetStatus(UartStatusEnum aStatus)
	{
		return (UART2->S1 & aStatus & 0xff) == aStatus;
	}

UInt8 iUart_GetData(void)
	{
		return UART2->D;
	}

void iUart_SetData(UInt8 aData)
	{
		UART2->D = aData;
	}

bool iUart_IsBufferEmpty(void)
	{
		return !(sUartRxBufStruct.BufferIsFull);
	}

UChar iUart_GetCharFromBuffer(void)
	{
		if (kUartRxBufSize > sUartRxBufStruct.OutIndex)
			{
				sUartRxBufStruct.OutIndex++;
			}
		else
			{
				sUartRxBufStruct.OutIndex = 0;
			}
		return sUartRxBufStruct.RxBuf[sUartRxBufStruct.OutIndex];
	}

#ifdef INTERRUPT__
void UART2_IRQHandler(void)
	{
		iUart_INTRx(UART2_IRQn);
		// remettre le flag RDRF à 0
		while (1 == UART2->S1);
		while (UART2->D);
	}
#endif
