/*
------------------------------------------------------------
Copyright 2019-2020 Haute Ecole ARC Ingénierie,
Switzerland. All rights reserved
------------------------------------------------------------
Nom du fichier : main.h
Auteur et Date : Steve Huguenin-Elie / 11.11.2019
But :						 Définition du point d'entrée du programme
								 et Inclusion des librairies utiles
Modifications

------------------------------------------------------------
*/

#include "mCpu.h"
#include "mSwitch.h"
#include "mLeds.h"
#include "mDelay.h"
#include "mLcd.h"

#ifndef MAIN_H_
#define MAIN_H_

int main(void);

//-------------------------------------------------------------------------
// Déclaration des constantes
//-------------------------------------------------------------------------
// Les temps d'attente pour chaque LED
#define kLedDelay (1000/1.0)
//-------------------------------------------------------------------------
// Déclaration des variables globales
//-------------------------------------------------------------------------
// Enumération des états possible de la machine d'état
typedef enum
{
kAffichage,
kWait1Sec
}AffStateMachineEnum;
// Variable de la machine d'état de l'affichage
static AffStateMachineEnum sAffState=kAffichage;
// Nu du Delay de chaque LED
static int sDelayLed=0;
// Tableau de l'état des erreurs
static bool sErrTab[8]={false,false,false,false,false,false,false,false};
// Compteur utilisé pour afficher l'état de chaque erreur
unsigned int sAlarmNb=kSw1;

#endif /* MAIN_H_ */
