
#ifndef TACHO_H
#define TACHO_H

#include<string>
#include<vector>
using namespace std;

// neste ficheiro .h so sao usados ponteiros
// esta declaracao e suficiente
// no Tacho.cpp faz-se #include "Ingrediente.h" porque
// nesse ficheiro precisamos de usar funcoes do ingrediente
// ver "inclusao circular" que esta no moodle

class Ingrediente;

class Tacho {
	// Os tachos não têm temperatura máxima, mas no mínimo, e inicialmente, têm 5 graus
	static const int TEMPMIN = 5;

    //Um tacho e uma coisa onde podem ser inseridos 
    //muitos ingredientes, de qualquer tipo
    // => vector de ponteiros para a classe base dos ingredientes
    // para que estes ponteiros para a classe base possam apontar para objectos 
    // das classes derivadas:batata, etc havendo so um vector
    // slides, capitulo de polimorfismo : upcasting
    vector<Ingrediente *> ingredientes;
    
    //ate uma certa quantidade (em g), que e a quantidade maxima do tacho
    int quantMax;
    
    // Um tacho esta a uma determinada temperatura.
    int temperatura;
    
    // funcao auxiliar
    int pesquisaIngrediente(Ingrediente * ing)const;
	void ingredientesReagemMudancaTemp();
public:
    Tacho(int qMax);
   
    // aumentar a temperatura
    void aumentaTemperatura ( int valor); 
    
    // diminuir a temperatura
    void diminuiTemperatura ( int valor); 

    
    // terminar o cozinhado
    // terminar o cozinhado significa que o tacho e esvaziado
    // e todos os ingredientes sao transferidos para algum outro lugar
    // (os ingredientes sao devolvidos pela funcao que faz isso 
    // e o tacho fica vazio)
    vector<Ingrediente *> terminarCozinhado();

	// inserir ingrediente (qualquer ingrediente)
	void acrescentaIngrediente(Ingrediente * ing);
    
    // Quando um ingrediente e inserido no tacho, 
    // passa a pertencer ao tacho 
    // (pode assumir que todos os ingredientes inseridos 
    // no tacho foram alocados dinamicamente)
    // ou seja:
    // quando o tacho for destruido os ingredientes nao sobrevivem
    // tem que ser destruidos imediatamente antes;
    // tem que haver um destrutor na classe Tacho
    // que destrua os ingredientes - objectos dinamicos
    // da classe Batata ou Agua
    virtual ~Tacho();
    
    // para que a classe seja robusta e funcione bem
    // na passagem de objectos seus por valor, retorno por valor, atribuicao, etc
    // tem que haver tambem construtor por copia
    Tacho(const Tacho& orig);
    
    // e operador atribuicao que dupliquem os objectos que o destrutor destroi
    Tacho & operator=(const Tacho & ob);

	// remover os ingredientes com status "a eliminar"
	void removeIngredientesAEliminar();
    
    // calcula quantidade total
    int getQuantidade()const;
    
    int getTemperatura()const;
    
    string getAsString()const;
    
    Ingrediente * pesquisaPrimeiroIngComNome(string nome) const;
    
};

#endif /* TACHO_H */

