//
//  Porto.cpp
//  Trabalho_Pratico
//
//  Created by Gabs on 13/11/2018.
//  Copyright © 2018 Gabs. All rights reserved.
//

#include "Porto.h"
Porto::Porto(char asp, int f, int m, int x, int y):Unidade(asp, f, x, y), isMainPorto(m){}

int Porto::getIsMainPorto()const{
    return isMainPorto;
}

void Porto::setAsMain(int i){
    isMainPorto = i;
}
