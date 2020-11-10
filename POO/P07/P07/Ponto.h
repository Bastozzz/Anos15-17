#include <string>

using namespace std;
class Ponto {
	int x, y;
public:
	Ponto(int x, int y);
	int getx();
	int gety();
	int getDistancia(Ponto a);
	Ponto&mover(int newx, int newy);
	string getAsString() const;
	~Ponto();
};

