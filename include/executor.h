#ifndef EXECUTOR_H
#define EXECUTOR_H
#include <istream>
#include <ostream>
#include <sstream>
#include "sistema.h"

using namespace std;

class Executor {
private:
	Sistema *sistema;
	stringstream ss;
	bool sair = false;

public:
	Executor(Sistema& sistema);

	string processar_linha(string linha);
	void iniciar(istream& in, ostream& out);
};

#endif

