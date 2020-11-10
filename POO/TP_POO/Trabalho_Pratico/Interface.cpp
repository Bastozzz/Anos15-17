#include "Interface.h"

using namespace std;

void Interface::start() {
  string input;
  string command;
  string filename;
  bool success = false;

  init_ncurses();
  init_color_pairs();
  init_windows();

  while (!success) {
    input = getCommand();

    istringstream iss(input);

    if(iss >> command) {
      if(command.compare("config") == 0) {
        if(iss >> filename) {
          int valor = simulacao.getDadosFich(filename);

          switch (valor) {
            case ERRO_ABERURA:
            printlog("Erro na abertura!");
            break;
            case ERRO_FORMATACAO:
            printlog("Erro na formatacao!");
            break;
            case ERRO_FECHO:
            printlog("Erro no fecho!");
            break;
            case ERRO_VALORES:
            printlog("Erro nos valores!");
            break;
            case ERRO_INCOMPLETO:
            printlog("Dados incompletos!");
            break;
            default:
            printlog("Configuracao concluida!\nSimulacao vai comecar!\n\nPressione qualquer tecla para comecar...");
            success = true;
            break;
          }
        } else {
          printlog("Erro de sintaxe: config <filename>");
        }
      } else if(command.compare("sair") == 0){
        printlog("Sistema a terminar\n\nPressione qualquer tecla para concluir...\n");
        getch();
        endwin();
        clear();
        exit(0);
      }
        else
            printlog("Comando \"" + command + "\" desconhecido");
    }
  }

  getch();
  reset_window_title(log, "Log");
  init_simula();
  endwin();
}

void Interface::init_ncurses() {
  initscr();
  start_color();
  cbreak();
  refresh();
}

void Interface::init_color_pairs() {
  init_pair(WATER_PAIR_1, COLOR_BLUE, COLOR_BLUE);
  init_pair(WATER_PAIR_2, COLOR_CYAN, COLOR_CYAN);
  init_pair(LAND_PAIR, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(PORT_PAIR, COLOR_GREEN, COLOR_BLACK);
  init_pair(ENEMY_PORT_PAIR, COLOR_RED, COLOR_BLACK);
  init_pair(BOAT_PAIR, COLOR_GREEN, COLOR_BLUE);
  init_pair(ENEMY_BOAT_PAIR, COLOR_RED, COLOR_BLUE);
}

void Interface::init_windows() {
  commands = newwin(3, 50, 0, 0);
  keypad(commands, true);
  title_window(commands, "Command Line");

  log = newwin(20, 50, 3, 0);
  title_window(log, "Log");
}

void Interface::init_simula() {
  istringstream iss;
  string input;
  string command;
  string filename;

  init_mapa(simulacao.getLinhas(), simulacao.getColunas());

  while(true) {
    printmapa();
    input = getCommand();

    istringstream iss(input);

    if(iss >> command){
      if(command.compare("exec") == 0){
        if(iss >> filename){
          int valor = getComandosFich(filename);

          switch (valor) {
            case ERRO_ABERURA:
            printlog("Erro na abertura!");
            break;
            case ERRO_FORMATACAO:
            printlog("Erro na formatacao!");
            break;
            case ERRO_FECHO:
            printlog("Erro no fecho!");
            break;
            case ERRO_VALORES:
            printlog("Erro nos valores!");
            break;
            case ERRO_INCOMPLETO:
            printlog("Dados incompletos!");
            break;
            default:
            printlog("Comandos de Ficheiro Lidos com Sucesso!");
            break;
          }
        }
        else
        printlog("Erro de sintaxe: exec <filename>");

      } else if(command.compare("prox") == 0){
          simulacao.moveBarcos();
      } else if(command.compare("compranav") == 0){
        char tipo;
        if(iss >> tipo){
            if(tipo == 'F' || tipo == 'G' || tipo == 'V' || tipo == 'E'){
                simulacao.compraBarco(tipo);
                printlog("Barco Comprado com Sucesso\n");
            }
            else
                printlog("Tipo de Barco desconhecido\n(Tipos Aceites: E/F/G/V)");
        }
        else
          printlog("[Erro] Segundo Argumento Invalido/não Inserido\n");
          
      } else if(command.compare("vendenav") == 0){
        printlog("Vender Navio To-Do\n");
      } else if(command.compare("lista") == 0){
        printlog("Listar Mundo To-Do\n");
        //simulacao.trataComando(command);
      } else if(command.compare("compra") == 0){
        printlog("Comprar Mercadorias To-Do\n");
        //simulacao.trataComando(command);
      } else if(command.compare("vende") == 0){
        printlog("Vender Mercadorias To-Do\n");
        //simulacao.trataComando(command);
      } else if(command.compare("move") == 0){
        printlog("Mover Navio To-Do\n");
        //simulacao.trataComando(command);
      } else if(command.compare("auto") == 0){
        printlog("Ativar 'auto-piloto' de Navio To-Do\n");
        //simulacao.trataComando(command);
      } else if(command.compare("stop") == 0){
        printlog("Parar Navio To-Do\n");
        //simulacao.trataComando(command);
      } else if(command.compare("pirata") == 0){
        printlog("Novo Navio Pirata To-Do\n");
        //simulacao.trataComando(command);
      } else if(command.compare("evpos") == 0){
        printlog("Criar Evento entre duas posicoes To-Do\n");
        //simulacao.trataComando(command);
      } else if(command.compare("evnav") == 0){
        printlog("Criar Evento que afete um Navio To-Do\n");
        //simulacao.trataComando(command);
      } else if(command.compare("moedas") == 0){
        printlog("Acrescentar Moedas To-Do\n");
        //simulacao.trataComando(command);
      } else if(command.compare("vaipara") == 0){// há dois
        printlog("Mover Navio para Determinada posicao To-Do\n");
        //simulacao.trataComando(command);
      } else if(command.compare("comprasold") == 0){
        printlog("Comprar Soldados To-Do\n");
        //simulacao.trataComando(command);
      } else if(command.compare("saveg") == 0){
        printlog("Guardar Jogo To-Do\n");
        //simulacao.trataComando(command);
      } else if(command.compare("loadg") == 0){
        printlog("Carregar Jogo To-Do\n");
        //simulacao.trataComando(command);
      } else if(command.compare("delg") == 0){
        printlog("Apagar Jogo Salvaguardado To-Do\n");
        //simulacao.trataComando(command);
      } else if(command.compare("sair") == 0){
        printlog("Sistema a terminar\n\nPressione qualquer tecla para concluir...\n");
        getch();
        endwin();
        clear();
        exit(0);
      }
      else {
        printlog("Comando \"" + command + "\" desconhecido");
      }
    }
  }
}

void Interface::init_mapa(int altura, int largura) {
  map = newwin((altura * 2) + 2, (largura * 2) + 2, 0, 51);
  title_window(map, "Mapa");
}

void Interface::printmapa() {
  vector<string> mapa = simulacao.getMapa();
  int agua = 0;
  int agualinha;
  int y = 1;
  int x = 1;
    
    
  for (int i = 0; i < mapa.size(); i++, y = i + 1, x = 1) {
    if(i != 0 && i % 2 == 0) agua = !agua;

    agualinha = agua;
    for (int j = 0; j < mapa[i].length(); j++) {
      if(j != 0 && j % 2 == 0) agualinha = !agualinha;
      switch (mapa[i].at(j)) {
        case '.':
        mvwprintw(map, y, x, (char *) &mapa[i].at(j));
        if(agualinha == 0) mvwchgat(map, y, x, 1, A_REVERSE, WATER_PAIR_1, NULL);
        else mvwchgat(map, y, x, 1, A_NORMAL, WATER_PAIR_2, NULL);
        x++;
        break;
        case '+':
        mvwprintw(map, y, x, (char *) &mapa[i].at(j));
        mvwchgat(map, y, x, -1, A_NORMAL, LAND_PAIR, NULL);
        x++;
        break;
        case 'A':
        mvwprintw(map, y, x, (char *) &mapa[i].at(j));
        mvwchgat(map, y, x, -1, A_NORMAL, PORT_PAIR, NULL);
        x++;
        break;
        case 'a':
        mvwprintw(map, y, x, (char *) &mapa[i].at(j));
        mvwchgat(map, y, x, -1, A_NORMAL, PORT_PAIR, NULL);
        x++;
        break;
        case 'B':
        mvwprintw(map, y, x, (char *) &mapa[i].at(j));
        mvwchgat(map, y, x, -1, A_NORMAL, ENEMY_PORT_PAIR, NULL);
        x++;
        break;
        case 'b':
        mvwprintw(map, y, x, (char *) &mapa[i].at(j));
        mvwchgat(map, y, x, -1, A_NORMAL, ENEMY_PORT_PAIR, NULL);
        x++;
        break;
        case 'F':
        case 'G':
        case 'V':
        case 'E':
        mvwprintw(map, y, x, (char *) &mapa[i].at(j));
        mvwchgat(map, y, x, -1, A_NORMAL, BOAT_PAIR, NULL);
        x++;
        break;
      }
    }
  }

  title_window(map, "Mapa");
  wrefresh(map);
}

void Interface::title_window(WINDOW *window, string title) {
  box(window, 0, 0);
  mvwprintw(window, 0, 3, title.c_str());
  wrefresh(window);
}

void Interface::reset_window(WINDOW *window) {
  wclear(window);
}

void Interface::reset_window_title(WINDOW *window, string title) {
  wclear(window);
  title_window(window, title);
}

void Interface::mvwprintwr(WINDOW *window, int y, int x, string text) {
  mvwprintw(window, y, x, text.c_str());
  wrefresh(window);
}

void Interface::mvwprintwr(WINDOW *window, int y, int x, char c) {
  mvwaddch(window, y, x, c);
  wrefresh(window);
}

void Interface::printlog(string text) {
  int y = 1;
  string output;
  stringstream ss(text);

  reset_window_title(log, "Log");

  while(getline(ss, output, '\n')) {
    mvwprintwr(log, y, 1, output);
    y++;
  }
}

string Interface::getCommand() {
  char input[50];

  reset_window_title(commands, "Command Line");
  mvwprintwr(commands, 1, 1, ">");
  wgetstr(commands, input);

  string command(input);

  return command;
}

int Interface::getComandosFich(string nomeFich){
  ifstream filename;
  string nomeF;

  filename.open(nomeFich);

  if (!filename.is_open()) {
    return ERRO_ABERURA;
  }

  string linhaLida;
  int i, lidos;
  bool mapalido;

  lidos = 0;
  mapalido = false;

  while (getline(filename, linhaLida)) {

    istringstream iss(linhaLida);
    i = 0;

    string command;
    iss >> command;
    if (!(iss)) {
      return ERRO_FORMATACAO;
    }
    if(iss >> command) {
      if(command.compare("Prox")){
        printlog("Iteracao de estado To-Do");
      } else if(command.compare("compranav")){
        string tipo;
        if(iss >> tipo){
          printlog("Comprar Barco\n");
          simulacao.compraBarco(tipo[0]);
          //printlog("Barco comprado com sucesso\n");
        }
        else
        printlog("[Erro] Segundo Argumento Invalido/não Inserido");
        if(tipo[0] == '0')
        printlog("Tipo de Barco invalido");
      } else if(command.compare("vendenav")){
        printlog("Vender Navio To-Do");
      } else if(command.compare("lista")){
        printlog("Listar Mundo To-Do");
        //simulacao.trataComando(command);
      } else if(command.compare("compra")){
        printlog("Comprar Mercadorias To-Do");
        //simulacao.trataComando(command);
      } else if(command.compare("vende")){
        printlog("Vender Mercadorias To-Do");
        //simulacao.trataComando(command);
      } else if(command.compare("move")){
        printlog("Mover Navio To-Do");
        //simulacao.trataComando(command);
      } else if(command.compare("auto")){
        printlog("Ativar 'auto-piloto' de Navio To-Do");
        //simulacao.trataComando(command);
      } else if(command.compare("stop")){
        printlog("Parar Navio To-Do");
        //simulacao.trataComando(command);
      } else if(command.compare("pirata")){
        printlog("Novo Navio Pirata To-Do");
        //simulacao.trataComando(command);
      } else if(command.compare("evpos")){
        printlog("Criar Evento entre duas posicoes To-Do");
        //simulacao.trataComando(command);
      } else if(command.compare("evnav")){
        printlog("Criar Evento que afete um Navio To-Do");
        //simulacao.trataComando(command);
      } else if(command.compare("moedas")){
        printlog("Acrescentar Moedas To-Do");
        //simulacao.trataComando(command);
      } else if(command.compare("vaipara")){// há dois
        printlog("Mover Navio para Determinada posicao To-Do");
        //simulacao.trataComando(command);
      } else if(command.compare("comprasold")){
        printlog("Comprar Soldados To-Do");
        //simulacao.trataComando(command);
      } else if(command.compare("saveg")){
        printlog("Guardar Jogo To-Do");
        //simulacao.trataComando(command);
      } else if(command.compare("loadg")){
        printlog("Carregar Jogo To-Do");
        //simulacao.trataComando(command);
      } else if(command.compare("delg")){
        printlog("Apagar Jogo Salvaguardado To-Do");
        //simulacao.trataComando(command);
      } else if(command.compare("sair")){
        printlog("Terminar Jogo To-Do");
        //simulacao.trataComando(command);
      }
      else {
        printlog("Comando \"" + command + "\" desconhecido");
      }
    }
  }

  filename.close();

  if (lidos != 16) {
    return lidos;
  }

  return 0;
}
