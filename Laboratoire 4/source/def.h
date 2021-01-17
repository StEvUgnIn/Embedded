/*
 * def.h
 *
 *  Created on: 4 nov. 2019
 *      Author: steve.huguenin
 */

#ifndef DEF_H_
#define DEF_H_

typedef enum bool
	{
	false = 0, true
	} bool;

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

#endif /* DEF_H_ */
