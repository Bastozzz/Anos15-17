#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "Unidade.h"
#include "Barco.h"
#include "Porto.h"
#define ERRO_ABERURA 101
#define ERRO_FORMATACAO 102
#define ERRO_FECHO 103
#define ERRO_VALORES 104
#define ERRO_INCOMPLETO 105

using namespace std;

class Simulacao{
    vector<Unidade> unidades;
    vector<vector<char> > minimapa;
    int linhas = 0;
    int colunas = 0;
    int moedas = 0;
    int probpirata = 0;
    int preconavio = 0;
    int precosoldado = 0;
    int precovendpeixe = 0;
    int precocompmercad = 0;
    int precovendmercad = 0;
    int soldadosporto = 0;
    int probevento = 0;
    int probtempestade = 0;
    int probsereias = 0;
    int probcalmaria = 0;
    int probmotim = 0;
public:
    int getLinhas();
    int getColunas();
    int getmoedas();
    int getProbPirata();
    int getPrecoNavio();
    int getPrecoSoldado();
    int getPrecoVendPeixe();
    int getPrecoCompMercad();
    int getPrecoVendMercad();
    int getSoldadosPorto();
    int getProbEvento();
    int getProbTempestade();
    int getProbSereias();
    int getProbCalmaria();
    int getProbMotim();
    int getDadosFich(string nomeFich);
    int novaLinhaMapa(string linha);
    vector<string> getMapa();
    bool charValido(char a);
    void compraBarco(char tipo);
    void moveBarcos();
    int verificaPosicao(int x, int y); //mudar
    bool verificaMapa();
    bool verificaPorto(int x, int y);
    bool verificaOutro(int x, int y);
    //char checkBoatAndPort(vector<Unidade> portos, vector<Unidade> barcos, int x, int y);
    char checkBoatAndPort(vector<Unidade> portos, Unidade Barco, int x, int y);
};
