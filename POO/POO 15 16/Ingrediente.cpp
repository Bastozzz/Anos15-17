#include<sstream>
using namespace std;

#include "Ingrediente.h"


// criação e inicialização da variavel static
// deve ser feita no ficheiro .cpp
int Ingrediente::ordem = 0;


 Ingrediente::Ingrediente(string s, int quant)
:nome(s), quantidade(quant), numSerie(++ordem), aEliminar(false) {
// ordem aumenta 1 cada vez que se constroi um objecto
// numSerie fica com o valor que ordem tiver no momento
// em que funciona o construtor
}

Ingrediente::~Ingrediente() {
}

string Ingrediente::getAsString()const {
    ostringstream oss;
    oss << "   N. de serie: " << numSerie << "\n   nome: "
            << nome << "\n   quantidade " << quantidade << "\n   eliminar " << aEliminar << endl;
    return oss.str();
}

int Ingrediente::getQuantidade() const {
        return quantidade;
}

string Ingrediente::getNome()const{
    return nome;
}

bool Ingrediente::isAEliminar() const {
	return aEliminar;
}

void Ingrediente::setAEliminar(bool status){
	aEliminar = status;
}

void Ingrediente::acrescentaQuantidade(int n){
	if (n > 0) {
		quantidade += n;
	}
}