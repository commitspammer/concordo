#include <string>
#include <ostream>
#include <vector>
#include <sstream>
#include "canaltexto.h"
#include "mensagem.h"
#include "usuario.h"

using namespace std;

CanalTexto::CanalTexto(string nome)
{
	this->nome = nome;
}

string CanalTexto::get_nome()
{
	return this->nome;
}

void CanalTexto::add_mensagem(Mensagem mensagem)
{
	this->mensagens.push_back(mensagem);
}

string CanalTexto::listar_mensagens(vector<Usuario>& usuarios)
{
	stringstream ss;
	for (auto& m : this->mensagens) {
		for (auto& u : usuarios) {
			if (m.get_enviada_por() == u.get_id()) {
				ss << u.get_nome() << " " << m.get_data_hora();
				ss  << ": " << m.get_conteudo() << endl;
				break;
			}
		}
	}

	if (ss.str().empty())
		return ">>>Este canal de texto ainda não tem mensagens...";
	return ss.str() + ">>>Fim!";
}
