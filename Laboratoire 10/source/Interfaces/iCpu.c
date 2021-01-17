/*
 ------------------------------------------------------------
 Copyright 2019-2020 Haute Ecole ARC Ingénierie,
 Switzerland. All rights reserved
 ------------------------------------------------------------
 Nom du fichier : iCpu.c
 Auteur et Date : Steve Huguenin-Elie / 11.11.2019
 Description dans le fichier iCpu.h
 ------------------------------------------------------------
 */

#include "def.h"
#include "iCpu.h"

void iCpu_CLKInit(void)
	{
		unsigned char *aMCGPtr;
		/* Passage en mode FEI */
		aMCGPtr = (unsigned char *)kMCG_C2;
		*aMCGPtr &= ~(0 | (1 << 5));
		*aMCGPtr |= (0 | (1 << 4) | (1 << 3) | (1 << 2)); // 0b0001_1100
		/* Passage en mode FBE */
		aMCGPtr = (unsigned char *)kMCG_C1;
		*aMCGPtr &= ~(0 | (1 << 6) | (1 << 5) | (1 << 2));
		*aMCGPtr |= (0 | (1 << 7) | (1 << 4) | (1 << 3)); // 0b010011000

		/*
		 * Attendre que l’oscillateur externe soit initialisé, que le clock source de la FLL soit
		 * le clock externe et que c’est bien l’horloge externe comme source du clock
		 * MCGOUTCLK (le clock source CPU et BUS), c’est-à-dire que l’on est passé en
		 * mode FBE
		 */
		aMCGPtr = (unsigned char *)kMCG_S;
		while (0 == (*aMCGPtr & (1 << 1))); // 0x2
		while ((*aMCGPtr & (1 << 4))); // 0xFFEF
		while (0x8 != ((*aMCGPtr & (1 << 3))|(*aMCGPtr & (1 << 2)))); // 0x8 // 0xFFFB

		/*
		 * le clock source de la PLL doit être compris entre 2 et 4MHz,
		 * donc 8 MHz / 4 = 2MHz (2Mhz et pas 4 Mhz)
		 */
		aMCGPtr = (unsigned char *)kMCG_C5;
		*aMCGPtr &= ~(0 | (1 << 4) | (1 << 3) | (1 << 2));
		*aMCGPtr |= (0 | (1 << 1) | (1 << 0)); // 0b00011 = 0x3

		/*
		 * Passage en mode PBE (PLL Bypass External Clock)
		 */
		aMCGPtr = (unsigned char *)kMCG_C6;
		*aMCGPtr &= ~(0 | (1 << 4) | (1 << 3) | (1 << 2) | (1 << 1) | (1 << 0));
		*aMCGPtr |= (0 | (1 << 6)); // 0x40

		/*
		 * Attendre que la source du clock CPU soit la PLL et attendre que le clock PLL
		 * soit stable.
		 */
		aMCGPtr = (unsigned char *)kMCG_S;
		while (0 == (*aMCGPtr & (1 << 5))); // 0x20
		while (0 == (*aMCGPtr & (1 << 6))); // 0x40

		/* Passage en mode PEE */
		aMCGPtr = (unsigned char *)kMCG_C1;
		*aMCGPtr &= ~(0|(1 << 7)|(1 << 6)); // 0x3F

		/* Attendre que la PLL soit la source du clock CPU */
		aMCGPtr = (unsigned char *)kMCG_S;
		while (0xC != ((*aMCGPtr & (1 << 3))|(*aMCGPtr & (1 << 2)))); // 0x8 + 0x4 -> 0xC
	}
