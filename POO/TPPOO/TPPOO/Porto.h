#include "Unidade.h"

class Porto : public Unidade{
  int isMainPorto;//0 para porto principal, 0 para porto 'derivado'
public:
  Porto(char asp, int f, int m, int x, int y);
  int getIsMainPorto()const;
  void setAsMain(int i);
};
