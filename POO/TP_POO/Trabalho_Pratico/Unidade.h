//
//  Unidade.h
//  Trabalho_Pratico
//
//  Created by Gabs on 13/11/2018.
//  Copyright © 2018 Gabs. All rights reserved.
//

#ifndef Unidade_h
#define Unidade_h

class Unidade{
    char aspeto; //tipo de unidade que é (barco, porto)
    int isFriend; //0 se for amigo, 1 se for inimigo
    int posx, posy;
    bool isBarco;
public:
    Unidade(char asp, int isF, int x, int y);
    Unidade();
    int getIsFriend()const;
    bool getIsBarco();
    void setIsBarco(bool value);
    void setIsFriend(int i);
    char getAspeto();
    void setAspet(char c);
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    bool isAtXY(int x, int y);
};
#endif /* Unidade_h */
