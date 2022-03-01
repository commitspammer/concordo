#include <string>
#include <ostream>
#include <sstream>
#include <algorithm>
#include "servidor.h"
#include "canaltexto.h"
#include "mensagem.h"

using namespace std;

Servidor::Servidor(int dono_id, string nome)
{
	this->usuario_dono_id = dono_id;
	this->nome = nome;
	this->descricao = "";
	this->codigo_convite = "";
	this->participantes_id.push_back(dono_id);
}

int Servidor::get_usuario_dono_id()
{
	return this->usuario_dono_id;
}

string Servidor::get_nome()
{
	return this->nome;
}

string Servidor::get_descricao()
{
	return this->descricao;
}

string Servidor::get_codigo_convite()
{
	return this->codigo_convite;
}

void Servidor::set_descricao(string descricao)
{
	this->descricao = descricao;
}

void Servidor::set_codigo_convite(string convite)
{
	this->codigo_convite = convite;
}

void Servidor::add_participante(int id)
{
	this->participantes_id.push_back(id);
}

void Servidor::remove_participante(int id)
{
	auto i = this->participantes_id.begin();
	while (i != this->participantes_id.end()) {
		if (*i == id) {
			this->participantes_id.erase(i);
			return;
		}
		++i;
	}
}

bool Servidor::eh_participante(int id)
{
	for (auto& p_id : this->participantes_id) {
		if (p_id == id)
			return true;
	}
	return false;
}

string Servidor::imprimir_participantes(vector<Usuario>& usuarios)
{
	stringstream ss;
	for (auto& u : usuarios) {
		if (this->eh_participante(u.get_id()))
			ss << "#" << u.get_id() << " " << u.get_nome() << endl;
	}

	if (ss.str().empty())
		return ">>>Este servidor nao possui usuarios ainda...";
	return ss.str() + ">>>Fim!";
}

void Servidor::add_canal_texto(CanalTexto& canal)
{
	this->canais_texto.push_back(canal);
}

void Servidor::remove_canal_texto(string nome)
{
	auto i = this->canais_texto.begin();
	while (i != this->canais_texto.end()) {
		if (i->get_nome() == nome) {
			this->canais_texto.erase(i);
			return;
		}
		++i;
	}
}

bool Servidor::eh_canal_texto(string nome)
{
	for (auto& ct : this->canais_texto) {
		if (ct.get_nome() == nome)
			return true;
	}
	return false;
}

string Servidor::imprimir_canais_texto()
{
	stringstream ss;
	for (auto& ct : this->canais_texto) {
		ss << "=> " << ct.get_nome() << endl;
	}

	if (ss.str().empty())
		return ">>>Este servidor nao possui canais de texto ainda...";
	return ss.str() + ">>>Fim!";
}

void Servidor::enviar_mensagem(Mensagem& mensagem, string nome_canal)
{
	for (auto& ct : this->canais_texto) {
		if (ct.get_nome() == nome_canal)
			ct.add_mensagem(mensagem);
	}
}

string Servidor::imprimir_mensagens(string canal_texto, vector<Usuario>& usuarios)
{
	for (auto& ct : this->canais_texto) {
		if (canal_texto == ct.get_nome())
			return ct.listar_mensagens(usuarios);
	}
	return ">>>Canal de texto inexistente...";
}
