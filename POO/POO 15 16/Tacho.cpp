#include<sstream>
using namespace std;

#include "Tacho.h"
#include "Ingrediente.h"


// Os tachos nao tem temperatura maxima, 
//mas no minimo, e inicialmente, tem 5 graus
Tacho::Tacho(int qMax): quantMax(qMax),temperatura(TEMPMIN) {

    // o vector fica inicializado pelo seu construtor por omissao
    // ficando vazio
    // porque o construtor de uma classe com membros objectos 
    // de outra classe (vector neste caso) chama sempre o construtor para 
    // esses membros, como nao especificamos argumentos para esse construtor
    // e chamado o construtor por omissao do vector
    // slides => capitulo de composicao de objectos
}

void Tacho::aumentaTemperatura ( int valor){
	if (valor <= 0) {
		return;
	}
    //Quanto mais quente estiver o tacho, mais dificil e aquece-lo:
    //a partir dos 50 graus, tentar aumentar a temperatura do tacho 
    // em G graus fara efectivamente subir a temperatura em apenas G/2 graus.
    if(temperatura >= 50){
        temperatura += valor/2;
    }else // temperatura < 50
        if(temperatura + valor <= 50){
        temperatura += valor;
    }else{ // temperatura < 50 e temperatura + valor > 50
        int a = 50 - temperatura; 
        int b = valor - a;
        temperatura = 50 + b/2;
    }
	// os ingredientes reagem a mudanca de temperatura
	ingredientesReagemMudancaTemp();
}


void Tacho::diminuiTemperatura ( int valor){ 
    if( valor <= 0){ 
        return;
    }
    // Os tachos nao tem temperatura maxima, 
    //mas no minimo, e inicialmente, tem 5 graus
    temperatura -= valor;
    if(temperatura < TEMPMIN){
            temperatura = TEMPMIN;
    } 
	// os ingredientes reagem a mudanca de temperatura
	ingredientesReagemMudancaTemp();
}

void Tacho::removeIngredientesAEliminar() {
	for (auto it = ingredientes.begin(); it != ingredientes.end(); ) {
		if (((*it)->isAEliminar())) {
			delete *it;
			it = ingredientes.erase(it);
		}
		else {
			++it;
		}
	}
}

vector<Ingrediente *> Tacho::terminarCozinhado(){
    vector<Ingrediente *> aux;
	for (Ingrediente * ing : ingredientes) {
        // copia os enderecos dos ingredientes para aux
        aux.push_back(ing);
    }
    //o tacho fica vazio
    ingredientes.clear();
    return aux;
}

int Tacho::getQuantidade()const{
    int soma = 0;
	for (Ingrediente * ing : ingredientes) {
        soma += ing->getQuantidade();
    }
	return soma;
}

int Tacho::getTemperatura()const{
    return temperatura;
}
// inserir ingredientes
void Tacho::acrescentaIngrediente( Ingrediente * ing){
    if( ing == nullptr){
        return;
    }
    // nao se acrescenta se ultrapasar a quantidade maxima
    if (getQuantidade() + ing->getQuantidade() > quantMax){
        return;
    }
    // ingrediente acrescentado ao tacho
	Ingrediente * acrescentado = ing->duplica();
	// para criar uma copia seguramente criada com new
	 ingredientes.push_back(acrescentado);
    
    // ingrediente reage a entrada no tacho
    Ingrediente * novo = acrescentado->reageEntradaNoTacho(this);
	// esta funcao pode decidir que alguns ingredientes sao para eliminar
	// e outros para acrescentar

	// eliminar os ingredientes que ficaram com o status "aEliminar" como true
	removeIngredientesAEliminar();

	// acrescentar eventualmente...
	if (novo != nullptr) {
		ingredientes.push_back(novo);
	}

}

string Tacho::getAsString()const {
    ostringstream oss;
    oss << "\nTacho: " << " Quant max " << quantMax 
            << " Temp " << temperatura << endl;
	for (Ingrediente * ing : ingredientes) {
        oss <<  ing->getAsString()<<endl;
    }
    oss << endl;
    return oss.str();
}


int Tacho::pesquisaIngrediente(Ingrediente * ing)const{
    for(unsigned int i = 0; i < ingredientes.size() ; i++){
         if(ingredientes[i]== ing){
            return i; // posicao no vector
        }
    }
    return -1; // posicao impossivel, nao se encontra
}

void Tacho::ingredientesReagemMudancaTemp(){
	vector<Ingrediente *> novos; // novos ingrediantes a acrescentar resultantes da mudanca de temperatura

	for (Ingrediente * ing : ingredientes) {
		Ingrediente * novo = ing->reageMudancaTemp(this);
		// esta funcao pode decidir que alguns ingredientes sao para eliminar
		// PERIGO: eliminar elementos de um vector que está a ser percorrido, sem os devidos cuidados
		// e outros para acrescentar
		if (novo != nullptr) {
			novos.push_back(novo);
		}
	}
	// eliminar os ingredientes que ficaram com o status "aEliminar" como true
	// agora numa funcao dedicada a esta tarefa com os cuidados necessarios
	removeIngredientesAEliminar();

	//acrescentar os ingredientes
	for (Ingrediente * novo : novos) {
		ingredientes.push_back(novo);
	}
}


Ingrediente * Tacho::pesquisaPrimeiroIngComNome(string nome) const{
	for (Ingrediente * ing : ingredientes) {
         if(ing->getNome() == nome){
            return ing; // endereco do primeiro
            // ingrediente com este nome
        }
    }
    return nullptr; // nao se encontra ingrediente com este nome
}


// slides: capitulo: classes com ponteiros para memoria dinamica e composicao
// operador atribuicao
Tacho & Tacho::operator=(const Tacho & ob){
    // prevencao da auto-atribuicao, atribuicao de um objecto a si proprio
    // esta feito: nesse caso => sair
    if(this == &ob){
        return *this;
    }
    // limpeza da memoria velha do primeiro membro da atribuicao
    // libertar os ingredientes apontados ...
	for (Ingrediente * ing : ingredientes) {
        delete ing;
    }
    // esvaziar o vector que agora so aponta para memoria ja nao reservada
    ingredientes.clear();
    
    // copiar a informacao de ob (que refere o segundo membro da atribuicao)
    //, duplicando os objectos dinamicos 
	for (Ingrediente * ing : ob.ingredientes) {
        // duplicacao polimorfica de um ingrediente da origem da copia
        Ingrediente * p = ing->duplica();
        // acrescenta-se o duplicado  para que depois de uma atribuicao
        // o destrutor nao faca duplo delete a um mesmo objecto 
        // em memoria dinamica
        ingredientes.push_back(p);
    }
    // nao esquecer os restantes membros
    quantMax = ob.quantMax;
    temperatura = ob.temperatura;
    
    return *this;
}
Tacho::Tacho(const Tacho& ob) {
    // nao ha ponteiros com valores lixo para limpar
    // funcionou o construtor por omissao do vector que criou
    // um vector vazio (sem ponteiros)
    
    // se houvesse ponteiros com valores lixo punham-se a nullptr
    // porque precisamos de preparar o objecto que esta a ser criado
    // para invocar o operador atribuicao que limpa a memoria velha
    // do objecto que o invoca, o primeiro membro da atribuicao
    *this = ob; // chama o operador atribuicao e copia os dados
    // de acordo com o que tem implementado: duplicando
    // a memoria dinamica que o destrutor liberta
}

Tacho::~Tacho() {
	for (Ingrediente * ing : ingredientes) {
        delete ing;
    }
}
