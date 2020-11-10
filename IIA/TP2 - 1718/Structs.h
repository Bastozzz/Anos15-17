//
//  Structs.h
//  TP2IIA
//
//  Created by Gabs on 22/12/2017.
//  Copyright © 2017 Gabriel Pinheiro nº 21260736. All rights reserved.
//

#ifndef Structs_h
#define Structs_h
#define tam 50

struct moeda
{
    float * moedas;
    int vTam;
    int nmax;
    float objetivo;
};

typedef struct moeda moedas, *pmoedas;
#endif /* Structs_h */
