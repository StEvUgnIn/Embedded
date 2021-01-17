/*
 ------------------------------------------------------------
 Copyright 2019-2020 Haute Ecole ARC Ingénierie,
 Switzerland. All rights reserved
 ------------------------------------------------------------
 Nom du fichier : def.h
 Auteur et Date : Steve Huguenin-Elie / 11.11.2019
 But :						 Définitions pour le projet
 Modifications

 ------------------------------------------------------------
 */

#ifndef DEF_H_
#define DEF_H_

#ifndef _STDBOOL_H
typedef enum bool
	{
	false = 0, true
	} bool;
#endif

#ifndef _STDINT_H
typedef unsigned char uint8_t;
#endif
#ifdef REQUIRE_STDINT
typedef char int8_t;
typedef short int int16_t;
typedef unsigned short int uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef long int64_t;
typedef unsigned long uint64_t;
#endif

#ifdef MRS232_H_
#define NULL ((void*)(0))
#endif

//-------------------------------------------------------------------------
// Déclaration des constantes
//-------------------------------------------------------------------------
// Registres de direction
#define kGPIOA_PDDR     (0x400FF014)
#define kGPIOB_PDDR     (0x400FF054)
#define kGPIOC_PDDR     (0x400FF094)
#define kGPIOD_PDDR     (0x400FF0D4)
#define kGPIOE_PDDR     (0x400FF114)

// Registre de données --> sortie
#define kGPIOA_PDOR     (0x400FF000)
#define kGPIOB_PDOR     (0x400FF040)
#define kGPIOC_PDOR     (0x400FF080)
#define kGPIOD_PDOR     (0x400FF0C0)
#define kGPIOE_PDOR     (0x400FF100)

// Registre de données --> entrée
#define kGPIOA_PDIR     (0x400FF010)
#define kGPIOB_PDIR     (0x400FF050)
#define kGPIOC_PDIR     (0x400FF090)
#define kGPIOD_PDIR     (0x400FF0D0)
#define kGPIOE_PDIR     (0x400FF110)

// Registre permettant de configurer la fonctionnalité des pins
#define kPORTA_PCR0			(0x40049000)
#define kPORTB_PCR0			(0x4004A000)
#define kPORTC_PCR0			(0x4004B000)
#define kPORTD_PCR0			(0x4004C000)
#define kPORTE_PCR0			(0x4004D000)

// Registres de configuration du MCG
#define kMCG_S 				  (0x40064006)
#define kMCG_C1 			  (0x40064000)
#define kMCG_C2   			(0x40064001)
#define kMCG_C3 			  (0x40064002)
#define kMCG_C4 			  (0x40064003)
#define kMCG_C5 			  (0x40064004)
#define kMCG_C6 			  (0x40064005)

// Registres de configuration du PIT
#define kSIM_SCGC6 			(0x4004803C)
#define kPIT_MCR				(0x40037000)
#define kPIT_LDVAL0			(0x40037100)
#define kPIT_LDVAL1			(0x40037110)
#define kPIT_TCTRL0 		(0x40037108)
#define kPIT_TCTRL1 		(0x40037118)
#define kPIT_TFLG0			(0x4003710C)
#define kPIT_TFLG1			(0x4003711C)
#define	kPIT_CVAL0			(0x40037104)
#define	kPIT_CVAL1			(0x40037114)

// Registres du vecteur d'interruptions
#define kNVIC_ISER			(0xE000E100)

// Registres IPR
#define	kNVIC_IPR0 					(0xE000E400)
#define kNVIC_IPR1 					(0xE000E404)
#define kNVIC_IPR2 					(0xE000E408)
#define kNVIC_IPR3 					(0xE000E40C)
#define kNVIC_IPR4 					(0xE000E410)
#define kNVIC_IPR5 					(0xE000E414)
#define kNVIC_IPR6 					(0xE000E418)
#define kNVIC_IPR7 					(0xE000E41C)

// Activer les interruptions masquables
#define EnableInterrupts __asm(" CPSIE i")

// Désactiver les interruptions masquables
#define DisableInterrupts __asm(" CPSID i")

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

typedef enum
	{
	kPIT0 = 0x0, kPIT1 = 0x10
	} PITEnum;

typedef enum
	{
	kEtat1 = 0x1,
	kEtat2 = 0x2,
	kEtat3 = 0x4,
	kEtat4 = 0x8,
	kEtat5 = 0x10,
	kEtat6 = 0x20,
	kEtat7 = 0x40,
	kEtat8 = 0x80
	} EtatEnum;

typedef enum
	{
	kTransmitDataRegEmpty = 0x80,
	kTransmitComplete = 0x40,
	kReceiveDataRegFull = 0x20,
	kIdleLineDetect = 0x10,
	kOverrunErr = 0x08,
	kNoiseErr = 0x04,
	kFramingErr = 0x02,
	kParityErr = 0x01
	} UartStatusEnum;

#define kEn (0|(0x4|0x8))

#endif /* DEF_H_ */
