//
//  Unidade.cpp
//  Trabalho_Pratico
//
//  Created by Gabs on 13/11/2018.
//  Copyright © 2018 Gabs. All rights reserved.
//

#include "Unidade.h"

Unidade::Unidade(char asp, int isF, int x, int y): posx(x), posy(y){
    isFriend = isF;
    aspeto = asp;
}

bool Unidade::getIsBarco(){
    return isBarco;
}

void Unidade::setIsBarco(bool value){
    isBarco = value;
}

int Unidade::getIsFriend()const{
    return isFriend;
}

void Unidade::setIsFriend(int i){
    isFriend = i;
}

char Unidade::getAspeto(){
    return aspeto;
}

void Unidade::setAspet(char c){
    aspeto = c;
}

int Unidade::getX(){
    return posx;
}

int Unidade::getY(){
    return posy;
}

void Unidade::setX(int x){
    posx = x;
}

void Unidade::setY(int y){
    posy = y;
}

Unidade::Unidade(){}

bool Unidade::isAtXY(int x, int y){
    if(x == this->posx && y == this->posy)
        return true;
    
    return false;
}
