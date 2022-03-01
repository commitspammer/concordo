#include <istream>
#include <ostream>
#include <iostream>
#include <sstream>
#include <queue>
#include "executor.h"

using namespace std;

// Função de apoio que recebe um istringstream e
// le todo texto restante até o fim da linha
string resto_de(istringstream &ss)
{
	string resto;
	getline(ss, resto, '\0'); // ler o resto da linha
	if (resto != "" && (resto[0] == ' ' || resto[0] == '\t')) {
		resto = resto.substr(1); // o primeiro caractere é um espaço, descartar
	}
	return resto;
}

// Construtor. Recebe uma referência ao sistema que vai operar
// Guarda o seu endereço para executar as operações.
Executor::Executor(Sistema &sistema)
{
	this->sair = false;
	this->sistema = &sistema;
}

// Método responsável por processar cada linha, capturando o nome do comando
// e seus parâmetros em variáveis e executar o método correspondente no sistema
string Executor::processar_linha(string linha)
{
	istringstream buf(linha);
	string nomeComando;
	buf >> nomeComando;

	if (nomeComando.empty()) {
		return ">>>Comando inválido (vazio)...";
	}
	if (nomeComando == "quit" ) {
		this->sair = true;
		return sistema->quit();
	}
	else if (nomeComando == "create-user") {
		string email, senha, nome;
		buf >> email;
		buf >> senha;
		nome = resto_de(buf);
		if (email.empty() || senha.empty() || nome.empty())
			return ">>>Uso: create-user EMAIL SENHA NOME";
		return sistema->create_user(email, senha, nome);
	}
	else if (nomeComando == "login") {
		string email, senha;
		buf >> email;
		buf >> senha;
		if (email.empty() || senha.empty())
			return ">>>Uso: login EMAIL SENHA";
		return sistema->login(email, senha);
	}
	else if (nomeComando == "list-users") {
		return sistema->list_users();
	}

	int id;
	if (!(buf >> id)) {
		return ">>>Comando precisa ser precedido de um ID [" + nomeComando + "]...";
	}

	if (nomeComando == "disconnect") {
		return sistema->disconnect(id);
	}
	else if (nomeComando == "create-server") {
		string nome;
		buf >> nome;
		if (nome.empty())
			return ">>>Uso: create-server ID NOME";
		return sistema->create_server(id, nome);
	}
	else if (nomeComando == "set-server-desc") {
		string nome, descricao;
		buf >> nome;
		descricao = resto_de(buf);
		if (nome.empty())
			return ">>>Uso: set-server-desc ID NOME [DESCRICAO...]";
		return sistema->set_server_desc(id, nome, descricao);
	}
	else if (nomeComando == "set-server-invite-code") {
		string nome, codigo;
		buf >> nome;
		buf >> codigo;
		if (nome.empty())
			return ">>>Uso: set-server-invite-code ID NOME [CODIGO]";
		return sistema->set_server_invite_code(id, nome, codigo);
	}
	else if (nomeComando == "list-servers") {
		return sistema->list_servers(id);
	}
	else if (nomeComando == "remove-server") {
		string nome;
		buf >> nome;
		if (nome.empty())
			return ">>>Uso: remove-server ID NOME";
		return sistema->remove_server(id, nome);
	}
	else if (nomeComando == "enter-server") {
		string nome, codigo;
		buf >> nome;
		buf >> codigo;
		if (nome.empty())
			return ">>>Uso: enter-server ID NOME [CODIGO]";
		return sistema->enter_server(id, nome, codigo);
	}
	else if (nomeComando == "leave-server") {
		string nome;
		buf >> nome;
		if (nome.empty())
			return ">>>Uso: leave-server ID NOME";
		return sistema->leave_server(id, nome);
	}
	else if (nomeComando == "list-participants") {
		return sistema->list_participants(id);
	}
	else if (nomeComando == "list-channels") {
		return sistema->list_channels(id);
	}
	else if (nomeComando == "create-channel") {
		string nome;
		buf >> nome;
		if (nome.empty())
			return ">>>Uso: create-channel ID NOME";
		return sistema->create_channel(id, nome);
	}
	else if (nomeComando == "enter-channel") {
		string nome;
		buf >> nome;
		if (nome.empty())
			return ">>>Uso: enter-channel ID NOME";
		return sistema->enter_channel(id, nome);
	}
	else if (nomeComando == "leave-channel") {
		return sistema->leave_channel(id);
	}
	else if (nomeComando == "send-message") {
		string mensagem;
		mensagem = resto_de(buf);
		if (mensagem.empty())
			return ">>>Uso: send-message ID MESSAGE...";
		return sistema->send_message(id, mensagem);
	}
	else if (nomeComando == "list-messages") {
		return sistema->list_messages(id);
	}
	else {
		return ">>>Comando não reconhecido [" + nomeComando + "]...";
	}
}

// Inicia o processamento dos comentarios.
// Esse método recebe por exemplo o "cin" e o "cout" no main
// Dessa forma ele faz o necessário para ler 1 comando por linha e
// o processar corretamente, colocando no stream de saída o resultado de cada um.
void Executor::iniciar(istream &inputStream, ostream &outputStream)
{
	string linha, saida;
	this->sair = false;
	while (!this->sair) {
		if (getline(inputStream, linha)) {
			saida = processar_linha(linha);
			outputStream << saida << endl;
		}
	}
}
