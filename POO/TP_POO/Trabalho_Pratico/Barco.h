//
//  Barco.h
//  Trabalho_Pratico
//
//  Created by Gabs on 13/11/2018.
//  Copyright © 2018 Gabs. All rights reserved.
//
#include "Unidade.h"
#define MAX_VELEIRO_FISH 40
#define MAX_VELEIRO_WATER 200
#define MAX_VELEIRO_SOLDIER 20
#define MAX_GALEAO_FISH 70
#define MAX_GALEAO_WATER 400
#define MAX_GALEAO_SOLDIER 40
#define MAX_ESCUNA_FISH 20
#define MAX_ESCUNA_WATER 100
#define MAX_ESCUNA_SOLDIER 10
#define MAX_FRAGATA_WATER 500
#define MAX_FRAGATA_SOLDIER 50
#define MAX_ESPECIAL_FISH 1001 // to be defined
#define MAX_ESPECIAL_WATER 1001 //to be defined
#define MAX_ESPECIAL_SOLDIER 1001 //to be defined


class Barco : public Unidade{
    int isFriend;//0 para amigo, 1 para inimigo
    int nSoldados;
    int tonPeixe;
    int agua;
    static int nBarco;//guarda o numero do barco
public:
    Barco(char aspeto, int isFr, int x, int y);
};

class Veleiro : public Barco{
public:
    Veleiro(char aspeto, int isFr, int x, int y);
};

class Galeao : public Barco{
public:
    Galeao(char aspeto, int isFr, int x, int y);
};

class Escuna : public Barco{
public:
    Escuna(char aspeto, int isFr, int x, int y);
};

class Fragata : public Barco{
public:
    Fragata(char aspeto, int isFr, int x, int y);
};

/*
class Especial : public Barco{
public:
    Especial(char aspeto, int isFr);
};
*/
