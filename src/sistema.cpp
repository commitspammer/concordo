#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <regex>
#include "sistema.h"
#include "usuario.h"
#include "servidor.h"
#include "canaltexto.h"

using namespace std;

/*  concatenates two streamable variables*/
template <typename StreamableT>
string cat(StreamableT s)
{
	stringstream ss;
	ss << s;
	return ss.str();
}

/*  concatenates various streamable variables recusvely */
template <typename StreamableHead, typename... StreamableTail>
string cat(StreamableHead h, StreamableTail... t)
{
	stringstream ss;
	ss << h;
	return ss.str() + cat(t...);
}

/* validates email string */
bool email_validate(string email)
{
    const regex email_regex ("\\w+@\\w+\\.[\\w\\.]+"); //creates a pattern for the email
    return regex_match(email, email_regex); //return true or false
}


/* COMANDOS */
string Sistema::quit()
{
	return ">>>Adios...";
}

string Sistema::create_user(const string email, const string senha, const string nome)
{
	if(!email_validate(email))
		return ">>>Email inválido...";
	for (auto& u : this->usuarios) {
		if (email == u.get_email())
			return ">>>Email já utilizado, brother...";
		if (nome == u.get_nome())
			return ">>>Nome já utilizado, brother...";
	}

	int id = this->usuarios.size() + 1;
	Usuario usuario(id, nome, email, senha);
	this->usuarios.push_back(usuario);
	return cat(">>>Usuario criado com sucesso, filhão! Seu ID: #", id);
}

string Sistema::login(const string email, const string senha)
{
	for (auto& u : this->usuarios) {
		if (email == u.get_email() && !u.igual_senha(senha))
			return ">>>Senha incorreta, consagrado...";

		if (email == u.get_email() && u.igual_senha(senha)) {
			if (this->usuarios_logados.count(u.get_id()))
				return ">>>Usuário já está logado...";

			this->usuarios_logados[u.get_id()] = make_pair("","");
			return ">>>Conectado com sucesso!";
		}
	}
	return ">>>Email nao cadastrado, consagrado...";
}

string Sistema::disconnect(int id)
{
	if (!this->usuarios_logados.count(id))
		return ">>>Usuário já está desconectado...";

	this->usuarios_logados.erase(id);
	return ">>>Desconectado com sucesso!";
}

string Sistema::create_server(int id, const string nome)
{
	if (!this->usuarios_logados.count(id))
		return ">>>Usuario não está logado...";

	for (auto& s : this->servidores) {
		if (nome == s.get_nome())
			return ">>>Servidor com este nome ja criado...";
	}

	Servidor servidor(id, nome);
	this->servidores.push_back(servidor);
	return ">>>Servidor criado com sucesso!";
}

string Sistema::set_server_desc(int id, const string nome, const string descricao)
{
	if (!this->usuarios_logados.count(id))
		return ">>>Usuario não está logado...";

	for (auto& s : this->servidores) {
		if (nome == s.get_nome()) {
			if (id != s.get_usuario_dono_id())
				return ">>>Usuario não é o dono do servidor...";

			s.set_descricao(descricao);
			if (descricao == "")
				return cat(">>> Descrição do servidor \"", s.get_nome(), "\" removida!");
			return cat(">>>Descrição do servidor \"", s.get_nome(),"\" criada!");
		}
	}
	return ">>>Servidor inexistente...";
}

string Sistema::set_server_invite_code(int id, const string nome, const string codigo)
{
	if (!this->usuarios_logados.count(id))
		return ">>>Usuario não está logado...";

	for (auto& s : this->servidores) {
		if (nome == s.get_nome()) {
			if (id != s.get_usuario_dono_id())
				return ">>>Usuario não é o dono do servidor...";

			s.set_codigo_convite(codigo);
			if (codigo == "")
				return cat(">>>Código de convite do servidor \"", s.get_nome(), "\" removido! Servidor aberto!");
			return cat(">>>Codigo de convite do servidor \"", s.get_nome(),"\" criado!");
		}
	}
	return ">>>Servidor inexistente...";
}

string Sistema::list_servers(int id)
{
	/* if (!this->usuarios_logados.count(id)) return ">>>Usuario não está logado..."; */

	if (this->servidores.empty())
		return ">>>Nenhum servidor foi criado ainda...";

	stringstream ss;
	for (auto& s : this->servidores) {
		ss << "=> " << s.get_nome() << " [\"" << s.get_descricao() << "\"] ";
		ss << "[DONO: #" << s.get_usuario_dono_id() << "]" << endl;
	}
	return ss.str() + ">>>Fim!";
}

string Sistema::remove_server(int id, const string nome)
{
	if (!this->usuarios_logados.count(id))
		return ">>>Usuario não está logado...";

	auto i = this->servidores.begin();
	while (i != this->servidores.end()) {
		if (i->get_nome() == nome) {
			if (i->get_usuario_dono_id() != id)
				return ">>>Usuario nao e dono do servidor...";

			for (auto& u : this->usuarios) {
				if (this->usuarios_logados[u.get_id()].first == nome) {
					this->usuarios_logados[u.get_id()].first = "";
					this->usuarios_logados[u.get_id()].second = "";
				}
			}
			this->servidores.erase(i);
			return ">>>Servidor removido com sucesso!";
		}
		++i;
	}
	return ">>>Servidor nao existe...";
}

string Sistema::enter_server(int id, const string nome, const string codigo)
{
	if (!this->usuarios_logados.count(id))
		return ">>>Usuario não está logado...";

	for (auto& s : this->servidores) {
		if (nome == s.get_nome()) {
			if (this->usuarios_logados[id].first == nome)
				return ">>>Usuário já está visualizando o servidor...";

			if (id != s.get_usuario_dono_id() && codigo != s.get_codigo_convite())
				return ">>>Código inválido...";

			this->usuarios_logados[id].first = nome;
			this->usuarios_logados[id].second = "";

			if (s.eh_participante(id))
				return ">>>Usuário entrou no servidor com sucesso!";

			s.add_participante(id);
			return ">>>Usuário entrou no servidor com sucesso! Bem-vindo!";
		}
	}
	return ">>>Servidor inexistente...";
}

string Sistema::leave_server(int id, const string nome)
{
	if (!this->usuarios_logados.count(id))
		return ">>>Usuario não está logado...";

	for (auto& s : this->servidores) {
		if (nome == s.get_nome()) {
			if (id == s.get_usuario_dono_id())
				return ">>Usuario e o dono do servidor...";

			if (!s.eh_participante(id))
				return ">>>Usuário nao e participante do servidor...";

			if (this->usuarios_logados[id].first == nome) {
				this->usuarios_logados[id].first = "";
				this->usuarios_logados[id].second = "";
			}
			s.remove_participante(id);
			return ">>>Usuário saiu do servidor com sucesso!";
		}
	}
	return ">>>Servidor inexistente...";
}

string Sistema::list_participants(int id)
{
	if (!this->usuarios_logados.count(id))
		return ">>>Usuario não está logado...";

	if (this->usuarios_logados[id].first.empty())
		return ">>>Usuario não está visualizando nenhum servidor...";

	for (auto& s : this->servidores) {
		if (s.get_nome() == this->usuarios_logados[id].first)
			return s.imprimir_participantes(this->usuarios);
	}
	return ">>>Servidor nao encontrado...";
}

string Sistema::list_channels(int id)
{
	if (!this->usuarios_logados.count(id))
		return ">>>Usuario não está logado...";

	if (this->usuarios_logados[id].first.empty())
		return ">>>Usuario não está visualizando nenhum servidor...";

	for (auto& s : this->servidores) {
		if (s.get_nome() == this->usuarios_logados[id].first)
			return s.imprimir_canais_texto();
	}
	return ">>>Servidor nao encontrado...";
}

string Sistema::create_channel(int id, const string nome)
{
	if (!this->usuarios_logados.count(id))
		return ">>>Usuario não está logado...";

	if (this->usuarios_logados[id].first.empty())
		return ">>>Usuario não está visualizando nenhum servidor...";

	for (auto& s : this->servidores) {
		if (s.get_nome() == this->usuarios_logados[id].first) {
			if (s.eh_canal_texto(nome))
				return ">>>Canal com esse nome ja existe...";

			CanalTexto canal(nome);
			s.add_canal_texto(canal);
			return ">>>Canal criado com sucesso!";
		}
	}
	return ">>>Usuario nao é dono do servidor...";
}

string Sistema::enter_channel(int id, const string nome)
{
	if (!this->usuarios_logados.count(id))
		return ">>>Usuario não está logado...";

	if (this->usuarios_logados[id].first.empty())
		return ">>>Usuario não está visualizando nenhum servidor...";

	if (!this->usuarios_logados[id].second.empty())
		return ">>>Usuario já está visualizando um canal de texto...";

	for (auto& s : this->servidores) {
		if (s.get_nome() == this->usuarios_logados[id].first) {
			if (s.eh_canal_texto(nome)){
				this->usuarios_logados[id].second = nome;
				return cat(">>>Usuário entrou no canal ", nome, "!");
			}
		}
	}
	return ">>>Canal de texto não encontrado...";
}

string Sistema::leave_channel(int id)
{
	if (!this->usuarios_logados.count(id))
		return ">>>Usuario não está logado...";

	if (this->usuarios_logados[id].first.empty())
		return ">>>Usuario não está visualizando nenhum servidor...";

	if (this->usuarios_logados[id].second.empty())
		return ">>>Usuario já não está visualizando nenhum canal de texto...";

	string c;
	c = this->usuarios_logados[id].second;
	this->usuarios_logados[id].second = "";
	return cat(">>>Usuario saiu do canal ", c, "!");
}

string Sistema::send_message(int id, const string conteudo)
{
	if (!this->usuarios_logados.count(id))
		return ">>>Usuario não está logado...";

	if (this->usuarios_logados[id].second.empty())
		return ">>>Usuario não está visualizando nenhum canal...";

	for (auto& s : this->servidores) {
		if (s.get_nome() == this->usuarios_logados[id].first) {
			if (!s.eh_canal_texto(this->usuarios_logados[id].second))
				return ">>>Canal nao existe no servidor...";

			Mensagem mensagem(id, conteudo);
			s.enviar_mensagem(mensagem, this->usuarios_logados[id].second);
			return ">>>Mensagem enviada com sucesso!";
		}
	}
	return ">>>Servidor nao encontrado...";
}

string Sistema::list_messages(int id)
{
	if (!this->usuarios_logados.count(id))
		return ">>>Usuario não está logado...";

	if (this->usuarios_logados[id].first.empty())
		return ">>>Usuario não está visualizando nenhum servidor...";

	if (this->usuarios_logados[id].second.empty())
		return ">>>Usuario não está visualizando nenhum canal de texto...";

	for (auto& s : this->servidores) {
		if (s.get_nome() == this->usuarios_logados[id].first) {
			return s.imprimir_mensagens(this->usuarios_logados[id].second, this->usuarios);
		}
	}
	return ">>>Servidor nao encontrado...";
}

/* IMPLEMENTAR MÉTODOS PARA OS COMANDOS RESTANTES */

/*** EXTRA METHODS ***/

string Sistema::list_users()
{
	if (this->usuarios.empty())
		return ">>>Nenhum usuario foi criado ainda...";

	stringstream ss;
	for (auto& u : this->usuarios) {
		ss << "#" << u.get_id() << " " << u.get_nome() << " [";

		if (this->usuarios_logados.count(u.get_id())) {
			ss << this->usuarios_logados[u.get_id()].first << " / ";
			ss << this->usuarios_logados[u.get_id()].second << "] ";
			ss << "[STATUS: on]" << endl;
		} else {
			ss << " / ] " << "[STATUS: off]" << endl;
		}
	}
	return ss.str() + ">>>Fim!";
}
