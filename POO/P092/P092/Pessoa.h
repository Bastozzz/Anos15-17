#include <string>

using namespace std;
class Pessoa {
	string nome;
	int cc, nif;
public:
	Pessoa(string nome, int cc, int nif);
	void setNome(string nnome);
	string getNome() const;
	int getCc() const;
	int getNif() const;
	string getAsString() const;
	~Pessoa();
};

