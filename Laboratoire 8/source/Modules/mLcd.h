/*
------------------------------------------------------------
Copyright 2019-2020 Haute Ecole ARC Ingénierie,
Switzerland. All rights reserved
------------------------------------------------------------
Nom du fichier : mLcd.h
Auteur et Date : Steve Huguenin-Elie / 11.11.2019
But :						 Commande et communication avec l'affichage
Modifications

------------------------------------------------------------
*/

#ifndef MLCD_H_
#define MLCD_H_

// configure les bits des ports B, C et E
void mLcd_Setup(void);

// configure, initialise et démarre le fonctionnement du LCD
void mLcd_Open(void);

// positionne AC en haut à gauche et affiche les caractères
void mLcd_WriteEntireDisplay(const char* aChar);

// écrit le caractère à la position X Y
void mLcd_Write(unsigned char aChar, unsigned int aXpos, unsigned int aYpos);

#endif /* MLCD_H_ */
