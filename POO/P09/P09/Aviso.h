#include <string>
#include "Prego.h"

using namespace std;
class Aviso {
	string txt;
	Prego const *p;
public:
	Aviso(string a, Prego *b);
	void mudaAviso(Prego *np);
	string getLocal();
	~Aviso();
};

