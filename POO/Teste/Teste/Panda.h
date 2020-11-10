#include <string>
#include <sstream>

using namespace std;
class Panda
{
	int idade;
	string pais;
	string especie;
	static int nPandas;
public:
	Panda(int idade, string pais = "China", string especie = "vermelho");
	static int quantosExistem();
	string getAsString();

	~Panda();
};




