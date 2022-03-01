#include <iomanip>
#include <ctime>
#include <string>
#include <sstream>
#include "mensagem.h"

using namespace std;

Mensagem::Mensagem(int enviada_por, string conteudo)
{
	this->enviada_por = enviada_por;
	this->conteudo = conteudo;

	time_t t = time(0);
	tm* now = localtime(&t);
	stringstream ss;
	ss.fill('0');
	ss << "<" << setw(2) << now->tm_mday << "/" << setw(2) << now->tm_mon+1;
	ss << "/" << setw(2) << now->tm_year-100; /* Only works in this century */
	ss << " - " << setw(2) << now->tm_hour << ":" << setw(2) << now->tm_min << ">";
	this->data_hora = ss.str();
}

string Mensagem::get_data_hora()
{
	return this->data_hora;
}

int Mensagem::get_enviada_por()
{
	return this->enviada_por;
}

string Mensagem::get_conteudo()
{
	return this->conteudo;
}
