#include <string>

using namespace std;
class Livro
{
	string nome;
	string autor;
public:
	Livro(string nome, string autor);
	string getNome();
	string getAutor();
	~Livro();
};

