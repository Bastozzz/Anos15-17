//
//  Barco.cpp
//  Trabalho_Pratico
//
//  Created by Gabs on 13/11/2018.
//  Copyright © 2018 Gabs. All rights reserved.
//

#include "Barco.h"

Barco::Barco(char asp, int isFr, int x, int y):Unidade(asp, isFr, x, y){
    isFriend = isFr;
    nBarco++;
    setIsBarco(true);
}

Veleiro::Veleiro(char aspeto, int isFr, int x, int y): Barco(aspeto, isFr, x, y){
    
}

Galeao::Galeao(char aspeto, int isFr, int x, int y): Barco(aspeto, isFr, x, y){
    
}

Escuna::Escuna(char aspeto, int isFr, int x, int y): Barco(aspeto, isFr, x, y){
    
}

Fragata::Fragata(char aspeto, int isFr, int x, int y): Barco(aspeto, isFr, x, y){
    
}

/*Especial::Especial(char aspeto, int isFr, int x, int y):Barco(aspeto, isFr, x, y){
 
 }*/
int Barco::nBarco = 0;
