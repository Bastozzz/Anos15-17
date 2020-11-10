#include <iostream>
#include <sstream>
#include <ncurses.h>
#include "Simulacao.h"
#define WATER_PAIR_1      1
#define WATER_PAIR_2      2
#define LAND_PAIR         3
#define PORT_PAIR         4
#define ENEMY_PORT_PAIR   5
#define BOAT_PAIR         6
#define ENEMY_BOAT_PAIR   7

using namespace std;
class Interface {
  WINDOW *commands, *log, *map;
  Simulacao simulacao;
  int logLine;
public:
  void start();
  void init_ncurses();
  void init_color_pairs();
  void init_windows();
  void init_simula();
  void init_mapa(int altura, int largura);
  void printmapa();
  void title_window(WINDOW *window, string title);
  void reset_window(WINDOW *window);
  void reset_window_title(WINDOW *window, string title);
  void mvwprintwr(WINDOW *window, int y, int x, string text);
  void mvwprintwr(WINDOW *window, int y, int x, char c);
  void printlog(string text);
  string getCommand();
  int getComandosFich(string nomeFich);
};
