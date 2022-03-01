#ifndef MENSAGEM_H
#define MENSAGEM_H
#include <string>

using namespace std;

class Mensagem {
private:
	string data_hora;
	int enviada_por;
	string conteudo;

public:
	/* @brief Constructor. Also data_hora is auto-generated.
	 * @param enviada_por Sender's ID.
	 * @param conteudo Message's content.
	 */
	Mensagem(int enviada_por, string conteudo);

	/* @brief Getters for attributes.
	 * @return Value of corresponding attribute.
	 */
	string get_data_hora();
	int get_enviada_por();
	string get_conteudo();
};

#endif

