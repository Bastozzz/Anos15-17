#include "Simulacao.h"

using namespace std;

int Simulacao::getLinhas(){
    return linhas;
}

int Simulacao::getColunas(){
    return colunas;
}

int Simulacao::getmoedas(){
    return moedas;
}

int Simulacao::getProbPirata(){
    return probpirata;
}

int Simulacao::getPrecoNavio(){
    return preconavio;
}

int Simulacao::getPrecoSoldado(){
    return precosoldado;
}

int Simulacao::getPrecoVendPeixe(){
    return precovendpeixe;
}

int Simulacao::getPrecoCompMercad(){
    return precocompmercad;
}

int Simulacao::getPrecoVendMercad(){
    return precovendmercad;
}

int Simulacao::getSoldadosPorto(){
    return soldadosporto;
}

int Simulacao::getProbEvento(){
    return probevento;
}

int Simulacao::getProbTempestade(){
    return probtempestade;
}

int Simulacao::getProbSereias(){
    return probsereias;
}

int Simulacao::getProbCalmaria(){
    return probcalmaria;
}

int Simulacao::getProbMotim(){
    return probmotim;
}

int Simulacao::getDadosFich(string nomeFich) {
    ifstream fich;

    fich.open(nomeFich);

    if (!fich.is_open()) {
        return ERRO_ABERURA;
    }

    string linhaLida;
    int i, lidos;
    bool mapalido;

    lidos = 0;
    mapalido = false;

    while (getline(fich, linhaLida)) {

        istringstream iss(linhaLida);
        i = 0;

        string comando;
        iss >> comando;
        if (!(iss)) {
            return ERRO_FORMATACAO;
        }

        if (comando == "linhas") {
            iss >> i;
            lidos++;
            if (i < 10) {
                return ERRO_VALORES;
            }
            linhas = i;
        }

        else if (comando == "colunas") {
            iss >> i;
            lidos++;
            if (i < 20) {
                return ERRO_VALORES;
            }
            colunas = i;
        }

        else if (comando.compare("moedas") == 0) {
            iss >> i;
            lidos++;
            moedas = i;
        }

        else if (comando.compare("probpirata") == 0) {
            iss >> i;
            lidos++;
            if (i > 100) {
                return ERRO_VALORES;
            }
            probpirata = i;
        }

        else if (comando.compare("preconavio") == 0) {
            iss >> i;
            lidos++;
            preconavio = i;
        }

        else if (comando.compare("precosoldado") == 0) {
            iss >> i;
            lidos++;
            precosoldado = i;
        }

        else if (comando.compare("precovendpeixe") == 0) {
            iss >> i;
            lidos++;
            precovendpeixe = i;
        }

        else if (comando.compare("precocompmercad") == 0) {
            iss >> i;
            lidos++;
            precocompmercad = i;
        }

        else if (comando.compare("precovendmercad") == 0) {
            iss >> i;
            lidos++;
            precovendmercad = i;
        }

        else if (comando.compare("soldadosporto") == 0) {
            iss >> i;
            lidos++;
            soldadosporto = i;
        }

        else if (comando.compare("probevento") == 0) {
            iss >> i;
            lidos++;
            probevento = i;
        }

        else if (comando.compare("probtempestade") == 0) {
            iss >> i;
            lidos++;
            probtempestade = i;
        }

        else if (comando.compare("probsereias") == 0) {
            iss >> i;
            lidos++;
            probsereias = i;
        }

        else if (comando.compare("probcalmaria") == 0) {
            iss >> i;
            lidos++;
            probcalmaria = i;
        }

        else if (comando.compare("probmotim") == 0) {
            iss >> i;
            lidos++;
            probmotim = i;
        }

        else{
            if (!mapalido) lidos++;
            mapalido = true;
            if(comando.size() != colunas) return ERRO_VALORES;
            if(novaLinhaMapa(comando) == 1) return ERRO_VALORES;
        }
    }

    fich.close();

    if (lidos != 16) {
        return lidos;
    }

    return 0;
}

int Simulacao::novaLinhaMapa(string linha) {
    vector<char> v;

    for (int i = 0; i < linha.length(); i++) {
        if(!charValido(linha.at(i))) {
            return 1;
        }

        v.push_back(linha.at(i));
    }

    minimapa.push_back(v);
    return 0;
}

bool Simulacao::verificaMapa(){
    int contaPrincipaisA = 0;
    int contaPrincipaisB = 0;
    bool result = true;
    for(int i = 0; i < minimapa.size(); i++){
        for(int j = 0; j < minimapa.at(i).size(); j++){
            if(minimapa[i][j] == 'A' || minimapa[i][j] == 'B'){
                if(minimapa[i][j] == 'A')
                    contaPrincipaisA++;
                if(minimapa[i][j] == 'B') {
                    contaPrincipaisB++;
                }
                Unidade a = Porto(minimapa[i][j], 0, 0, j, i);
                if(contaPrincipaisA > 1 || contaPrincipaisB > 1)
                    return false;
                if(minimapa[i + 1][j] == '+' || minimapa[i + 1][j + 1] == '+' || minimapa[i + 1][j - 1] == '+' || minimapa[i][j + 1] == '+' || minimapa[i][j - 1] == '+' || minimapa[i - 1][j] == '+' || minimapa[i - 1][j - 1] == '+' || minimapa[i - 1][i + 1 == '+'])
                    result = true;
                else
                    return  false;
                if(minimapa[i + 1][j] == '.' || minimapa[i + 1][j + 1] == '.' || minimapa[i + 1][j - 1] == '.' || minimapa[i][j + 1] == '.' || minimapa[i][j - 1] == '.' || minimapa[i - 1][j] == '.' || minimapa[i - 1][j - 1] == '.' || minimapa[i - 1][i + 1 == '.'])
                    result = true;
                else
                    return  false;

                unidades.push_back(a);
            }
            else if(minimapa[i][j] == 'a' || minimapa[i][j] == 'b'){
                Unidade a = Porto(minimapa[i][j], 0, 0, j, i);
                if(minimapa[i + 1][j] == '+' || minimapa[i + 1][j + 1] == '+' || minimapa[i + 1][j - 1] == '+' || minimapa[i][j + 1] == '+' || minimapa[i][j - 1] == '+' || minimapa[i - 1][j] == '+' || minimapa[i - 1][j - 1] == '+' || minimapa[i - 1][i + 1 == '+'])
                    result = true;
                else
                    return  false;
                if(minimapa[i + 1][j] == '.' || minimapa[i + 1][j + 1] == '.' || minimapa[i + 1][j - 1] == '.' || minimapa[i][j + 1] == '.' || minimapa[i][j - 1] == '.' || minimapa[i - 1][j] == '.' || minimapa[i - 1][j - 1] == '.' || minimapa[i - 1][i + 1 == '.'])
                    result = true;
                else
                    return  false;
                unidades.push_back(a);
            }
        }//for j
    }//for i
    return result;
}

vector<string> Simulacao::getMapa(){
    string linha;
    vector<string> mapa;
    vector<Unidade> barcos;
    vector<Unidade> portos;

    for(int i = 0; i < unidades.size(); i++){
        if(unidades[i].getIsBarco())
            barcos.push_back(unidades[i]);
    }

    for(int i = 0; i < unidades.size(); i++)
        if(unidades[i].getAspeto() == 'A')
            portos.push_back(unidades[i]);

    for (int i = 0; i < minimapa.size(); i++) {
        char c;
        linha.clear();
        for (int j = 0; j < minimapa[i].size(); j++) {
            c = minimapa[i][j];

            if(minimapa[i][j] != 'A' &&
               minimapa[i][j] != 'a' &&
               minimapa[i][j] != 'B' &&
               minimapa[i][j] != 'b')
                for(int k = 0; k < barcos.size(); k++){
                    if(barcos[k].isAtXY(j, i) == true){
                        c = barcos[k].getAspeto();
                    }
                }

            linha.push_back(c);

            linha.push_back(c);
        }
        mapa.push_back(linha);
        mapa.push_back(linha);
    }

    return mapa;
}

bool Simulacao::charValido(char a) {
    if (a == 'a' ||
        a == 'A' ||
        a == 'b' ||
        a == 'B' ||
        a == '+' ||
        a == '.') {
        return true;
    }
    return false;
}

void Simulacao::compraBarco(char tipo){
    Unidade nova;
    for(int i = 0; i < minimapa.size(); i++){
        for(int j = 0; j < minimapa.at(i).size(); j++){
            if(minimapa[i][j] == 'A'){
                switch (tipo) {
                    case 'V':
                        nova = Veleiro('V', 0, j, i);
                        unidades.push_back(nova);
                        break;
                    case 'G':
                        nova = Galeao('G', 0, j, i);
                        unidades.push_back(nova);
                        break;
                    case 'E':
                        nova = Escuna('E', 0, j, i);
                        unidades.push_back(nova);
                        break;
                    case 'F':
                        nova = Fragata('F', 0, j, i);
                        unidades.push_back(nova);
                        break;
                }
            }
        }
    }
}

void Simulacao::moveBarcos(){
    srand(time(NULL));

    for(int i = 0; i < unidades.size(); i++){
        if(unidades[i].getIsBarco() == true){
            int dir = (rand() % 8) + 1;
            int newX = 0, newY = 0;
            switch (dir) {
                case 1:
                    newX = unidades[i].getX() - 1;
                    newY = unidades[i].getY() - 1;
                    break;
                case 2:
                    newX = unidades[i].getX();
                    newY = unidades[i].getY() - 1;
                    break;
                case 3:
                    newX = unidades[i].getX() + 1;
                    newY = unidades[i].getY() - 1;
                    break;
                case 4:
                    newX = unidades[i].getX() + 1;
                    newY = unidades[i].getY();
                    break;
                case 5:
                    newX = unidades[i].getX() + 1;
                    newY = unidades[i].getY() + 1;
                    break;
                case 6:
                    newX = unidades[i].getX();
                    newY = unidades[i].getY() + 1;
                    break;
                case 7:
                    newX = unidades[i].getX() - 1;
                    newY = unidades[i].getY() + 1;
                    break;
                case 8:
                    newX = unidades[i].getX() - 1;
                    newY = unidades[i].getY();
                    break;
                default:
                    break;
            }
            if(newX < 0)
                newX = colunas - 1;
            if(newY < 0)
                newY = linhas -1;
            if(newX > colunas - 1)
                newX = 0;
            if(newY > linhas - 1)
                newY = 0;
            if(verificaPosicao(newX, newY) == 0 || verificaPosicao(newX, newY) == 1){
                unidades[i].setX(newX);
                unidades[i].setY(newY);
            }
        }
    }
}

int Simulacao::verificaPosicao(int x, int y){
    if(minimapa[y][x] == '.')
        return 0;
    if(minimapa[y][x] == 'A' || minimapa[y][x] == 'a' || minimapa[y][x] == 'B' || minimapa[y][x] == 'b')
        return 1;

    return -1;
}

char Simulacao::checkBoatAndPort(vector<Unidade> portos, Unidade Barco, int x, int y){
    for(int i = 0; i < portos.size(); i++)
        if(portos[i].isAtXY(x, y) == true && Barco.isAtXY(x, y) == true)
            return portos[i].getAspeto();
    return Barco.getAspeto();
}
