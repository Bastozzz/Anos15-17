#include<sstream>
using namespace std;

#include "Tacho.h"
#include "Fogao.h"

Fogao::Fogao(int num) {
    tempo = 0; //relogio interno que começa em 0
    n = num;
    // criar um array dinamico de n ponteiros para tachos
    tachos = new Tacho*[num]; 

    // colocar osponteiros todos a nullptr
    for( int i = 0 ; i < n ; ++i){
        tachos[i] = nullptr;
    }
}

Fogao::Fogao(const Fogao& orig) {
    // preparar o objecto nascente que tem os ponteiros e ints a lixo
    // para executar a "limpeza" de memoria velha feita no operador atribuicao
    n = 0;
	tachos = nullptr;

    // depois, invocar o operador atribuicao em que o novo objecto
    // é o primeiro membro e orig o segundo membro com
    // o processo feito no operador atribuição  
    *this = orig;
}
Fogao & Fogao::operator=(const Fogao & orig){
    // prevencao da auto-atribuicao, atribuicao de um objecto a si proprio
    // nesse caso => sair
    if(this == &orig){
        return *this;
    }
    // limpeza da memoria velha do primeiro membro da atribuicao
    // libertar os tachos apontados ...
    for( int i = 0 ; i < n ; ++i){
        delete tachos[i];
    }
    // libertar o array din. de ponteiros para tachos
    // nao esquecer: array =>  []
    delete [] tachos;

	// limpar os atributos
	tachos = nullptr;
	n = 0;

	// se a origem da copia for um objecto vazio...
	if (orig.n == 0 || orig.tachos == nullptr) {
		return *this;
	}
   
    // criar um array dinamico de orig.n ponteiros para tachos
    // do tamanho do que tem a origem da copia
    tachos = new Tacho*[orig.n]; 
    n = orig.n; // numero de tachos no fogao  
    // copiar a informacao de orig (que refere o segundo membro da atribuicao)
    //, duplicando os objectos dinamicos 
    for( int i = 0 ; i < orig.n ; ++i){
         Tacho * p = orig.tachos[i];
         if(p != nullptr){
            tachos[i] = new Tacho(*p); // construido por copia
         }
         else{
             tachos[i] = nullptr;
         }
    }
    // nao esquecer o restante membro    
    tempo = orig.tempo;
    return *this;
}
Fogao::~Fogao() {
    // libertar os tachos apontados
    for( int i = 0 ; i < n ; ++i){
        delete tachos[i];
    }
    // libertar o array din. de ponteiros para tachos
    // nao esquecer: array =>  []
    delete [] tachos;
}

// metodo para colocar um tacho na posição j
void Fogao::colocarTacho( int posicao, Tacho * t){
    if( posicao < 0 || posicao >= n){ // se esta fora dos limites
        return; // nao pode colocar
    }
	if (t == nullptr) {
		return;
	}
    // se ja estivesse ocupado, o tacho la existente e primeiro eliminado
    delete tachos[posicao]; // se estivesse nullptr esta instrucao nao faria nada 
    tachos[posicao] = new Tacho(*t);
}
// O fogao tem um metodo para aumentar a temperatura 
// em G graus, o que fara tambem aumentar a temperatura dos tachos
void Fogao::aumentaTemp( int g){
     for( int i = 0 ; i < n ; ++i){
        if(tachos[i] != nullptr)
            tachos[i]->aumentaTemperatura(g);
    }   
}

// O fogao tem tambem uma funcao que permite fazer passar M minutos
void Fogao::passaMinutos( int m){
	for (int t = tempo; t < tempo + m; ++t) {
		if (t % 2 == 0) {
			for (int i = 0; i < n; ++i) {
				if (tachos[i] != nullptr) {
					tachos[i]->diminuiTemperatura(1);
				}
			}
		}
	}
	tempo += m;
}

// Deve tambem ser possivel acrescentar tachos (na primeira posicao vazia) da seguinte forma
// fogao1 << tacho1 << tach2; // etc. mais tachos
// ver slides capitulo de operadores para justificar a importancia de retornar Fogao&
Fogao & Fogao::operator << ( Tacho & ob){
     for( int i = 0 ; i < n ; ++i){
         if(tachos[i] == nullptr){
             colocarTacho( i, &ob);
             // assim que coloca sai
             return *this;
         }
     }
     return *this;
}

// Ao fazer fogao += val_inteiro, o relogio interno do fogão avanca 
// valor_inteiro minutos
// ver slides capitulo de operadores para justificar a importancia de retornar Fogao&
Fogao & Fogao::operator += ( int tempo){
    passaMinutos( tempo);
    return *this;
}


string Fogao::getAsString()const {
    ostringstream oss;
    oss << "\nFogao com n: " << n << " tachos e " << tempo << " tempo\n";
    for( int i = 0 ; i < n ; ++i){
        if(tachos[i] != NULL){
                oss << tachos[i]->getAsString();
        }
    }
    oss << endl;
    return oss.str();
}