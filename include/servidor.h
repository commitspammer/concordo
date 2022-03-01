#ifndef SERVIDOR_H
#define SERVIDOR_H
#include <string>
#include <vector>
#include "canaltexto.h"
#include "usuario.h"
#include "mensagem.h"

using namespace std;

class Servidor {
private:
	int usuario_dono_id;
	string nome;
	string descricao;
	string codigo_convite;
	vector<CanalTexto> canais_texto;
	vector<int> participantes_id;

public:
	/* @brief Constructor. Also descricao, codigo_convite,
	 * canais_texto and participantes_id start empty.
	 * @param usuario_dono_id Owner's ID.
	 * @param nome Server's name.
	 */
	Servidor(int usuario_dono_id, string nome);

	/* @brief Getters for attributes.
	 * @return Value of corresponding attribute.
	 */
	int get_usuario_dono_id();
	string get_nome();
	string get_descricao();
	string get_codigo_convite();

	/* @brief Setters for attributes.
	 * @param New corresponding value to be set.
	 */
	void set_descricao(string descricao);
	void set_codigo_convite(string codigo);

	/* @brief Adds an ID to participantes_id.
	 * @param id ID to be added.
	 */
	void add_participante(int id);

	/* @brief Removes first instance of an ID from participantes_id.
	 * @param id ID to be removed.
	 */
	void remove_participante(int id);

	/* @brief Checks if an ID is in participantes_id.
	 * @param id ID to be checked.
	 * @return True if ID is in participantes_id; false if it isn't.
	 */
	bool eh_participante(int id);

	/* @brief Builds a string listing all participants in participantes_id.
	 * @param usuarios List of all available users.
	 * @return Formated list of participants.
	 */
	string imprimir_participantes(vector<Usuario>& usuarios);

	/* @brief Adds a CanalTexto object to canais_texto.
	 * @param canal CanalTexto object to be added.
	 */
	void add_canal_texto(CanalTexto& canal);

	/* @brief Removes first instance of a CanalTexto from canais_texto.
	 * @param nome Name of the channel to be removed.
	 */
	void remove_canal_texto(string nome);

	/* @brief Checks if a CanalTexto object is in canais_texto.
	 * @param nome Name of the channel to be checked.
	 * @return True if a channel with given name is in canais_texto;
 	 * false if it isn't.
	 */
	bool eh_canal_texto(string nome);

	/* @brief Builds a string listing all channels in canais_texto.
	 * @return Formated list of channels.
	 */
	string imprimir_canais_texto();

	/* @brief Sends a request to a CanalTexto from canais_texto to
	 * add a Mensagem to its list of messages.
	 * @param mensagem Mensagem to be added.
	 * @param nome_canal Name of the channel to request to.
	 */
	void enviar_mensagem(Mensagem& mensagem, string nome_canal);

	/* @brief Sends a request to a CanalTexto from canais_texto to
	 * generate a formated list of messages.
	 * @param nome_canal Name of the channel to request to.
	 * @param usuarios List of available users.
	 * @return Formated list of messages.
	 */
	string imprimir_mensagens(string nome_canal, vector<Usuario>& usuarios);
};

#endif

