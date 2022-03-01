#ifndef CANALTEXTO_H
#define CANALTEXTO_H
#include <string>
#include <vector>
#include "mensagem.h"
#include "usuario.h"

using namespace std;

class CanalTexto {
private:
	string nome;
	vector<Mensagem> mensagens;

public:
	/* @brief Constructor. Also mensagens starts empty.
	 * @param nome Channel's name.
	 */
	CanalTexto(string nome);

	/* @brief Getters for attributes.
	 * @return Value of corresponding attribute.
	 */
	string get_nome();

	/* @brief Adds a Mensagem object to mensagens.
	 * @param mensagem Mensagem object to be added.
	 */
	void add_mensagem(Mensagem mensagem);

	/* @brief Builds a string listing all messages in mensagens.
	 * @param usuarios List of all available users.
	 * @return Formated list of messages.
	 */
	string listar_mensagens(vector<Usuario>& usuarios);
};

#endif

