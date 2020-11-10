
#ifndef FOGAO_H
#define FOGAO_H

#include<string>
using namespace std;

class Tacho;

class Fogao {
    Tacho ** tachos; // ponteiro para array dinamico de ponteiros para tachos
    int n; // numero de tachos no fogao
    
    int tempo; // relogio interno
public:
    Fogao(int num);

	// Quando um tacho é colocado no fogão fica com o seu destino associado ao do fogão; 
	// um tacho nunca está em dois fogões ao mesmo tempo e se o fogão pegar fogo, o tacho também arde.
	// relacao entre fogao e tacho: composicao
    Fogao(const Fogao& orig);
    Fogao & operator=(const Fogao & orig);
    virtual ~Fogao();
    
    // metodo para colocar um tacho na posição j
   void colocarTacho( int posicao, Tacho * t);
    
    // O fogao tem um metodo para aumentar a temperatura 
    // em G graus, o que fara tambem aumentar a temperatura do tacho
    void aumentaTemp( int g);
    
    // O fogao tem tambem uma funcao que permite fazer passar M minutos
    void passaMinutos( int m);
    
    // Deve tambem ser possivel acrescentar tachos (na primeira posicao vazia) da seguinte forma
    // fogao1 << tacho1 << tach2; // etc. mais tachos
    Fogao & operator << ( Tacho & ob);
    
    // Ao fazer fogao += val_inteiro, o relogio interno do fogão avanca 
    // valor_inteiro minutos
    Fogao & operator += ( int tempo);
    
    string getAsString()const;
};

#endif /* FOGAO_H */

