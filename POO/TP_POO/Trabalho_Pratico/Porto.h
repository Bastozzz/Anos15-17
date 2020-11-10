//
//  Porto.h
//  Trabalho_Pratico
//
//  Created by Gabs on 13/11/2018.
//  Copyright © 2018 Gabs. All rights reserved.
//

#ifndef Porto_h
#define Porto_h
#include "Unidade.h"

class Porto : public Unidade{
    int isMainPorto;//0 para porto principal, 0 para porto 'derivado'
public:
    Porto(char asp, int f, int m, int x, int y);
    int getIsMainPorto()const;
    void setAsMain(int i);
};
#endif /* Porto_h */
