#include <string>

using namespace std;
class Prego {
	int x, y;
public:
	Prego(int a, int b);
	void mudaDeSitio(int nx, int ny);
	string getAsString() const;
	~Prego();
};

