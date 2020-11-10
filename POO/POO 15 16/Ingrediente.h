
#ifndef INGREDIENTE_H
#define INGREDIENTE_H

#include<string>
using namespace std;

// declaracao da existencia de um nome Tacho
// neste ficheiro do vai ser usado um ponteiro para Tacho
// por isso esta declaracao e suficiente
// se um objecto Tacho fosse membro desta classe por exemplo,
// seria preciso #include "Tacho.h"
// ver "inclusao circular" no moodle
class Tacho;

class Ingrediente {
    static int ordem; // para obter um  numero de serie sequencial
    // gerado automaticamente
    // variavel static existe uma so versão fora dos objectos
    int numSerie; // numero de serie
    string nome;
    int quantidade;
	bool aEliminar;
protected:
	void setAEliminar(bool status);
public:
	//   Nenhum ingrediente podera existir 
	//   sem ter os seus dados completamente definidos
    Ingrediente( string s, int quant);
    
    // boa pratica a existencia de destrutor virtual
    // nos slides ->capitulo de polimorfismo
    // esta explicada a razao
    virtual ~Ingrediente();
    
    //Os ingredientes tem um comportamento especifico 
    // quanto ao que acontece quando são inseridos num tacho
    virtual Ingrediente * reageEntradaNoTacho( Tacho * tacho) = 0;

    // e quanto ao que acontece quando a temperatura 
    // do cozinhado onde se encontram muda
    virtual Ingrediente *  reageMudancaTemp( Tacho * tacho) = 0;
    // So se sabe o que sao estes comportamentos quando se fala 
    // de ingredientes concretos (ex., cenouras, alhos).
    // aqui nao se sabe => funcoes abstractas
    // => esta classe fica abstracta
    // Existem varios tipos de ingredientes e 
    // neste momento nao se esta a falar de nada concreto.

	// Estes comportamentos/funcoes podem precisar de invocar funcoes 
	// do seu contexto (Tacho) para tomar as suas decisoes
	// recebem Tacho * como parâmetro
    
    virtual string getAsString()const;
    
    // implementa uma duplicacao (polimorfica) de cada objecto
    // para aplicar no construtor por copia e operador atribuicao do Tacho
    virtual Ingrediente * duplica()const = 0;
    int getQuantidade() const;
    string getNome()const;
	bool isAEliminar() const;
    void acrescentaQuantidade(int n);
};

#endif /* INGREDIENTE_H */

