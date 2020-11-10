#include "Gerador.h"

double getUniform01() {
	static default_random_engine e(time(0));
	static uniform_real_distribution<double> d(0.0, 0.1);

	return d(e);
}
