#include <string>
#include "Peixe.h"
#include <vector>

using namespace std;
class Aquario {
	string nome;
	vector<Peixe*> v;
public:
	Aquario(string a);
	void alimenta(int alimento);
	void addPeixe(Peixe *p);
	~Aquario();
};

ostream& operator<<(ostream& os, const Aquario& a) {
	os << NULL;
	return os;
}

