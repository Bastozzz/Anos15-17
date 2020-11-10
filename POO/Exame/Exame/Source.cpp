#include <iostream>
#include <string>
#include "Source.h"
using namespace std;

class Teste {
	int num;
public:
	Teste() :num(0) {}
	int getNum() { return num; }
	void setNum(int n) { num = n; }
};
void func1(Teste & a, const Teste & b) {
	a.setNum(2);
	cout << a.getNum();
}
void func2(const Teste * p1, Teste * const p2) {
	p1->setNum(2);
	p1 = p2;
	p2->setNum(4);
	p2 = p2;
}

int main() {

	getchar();
}