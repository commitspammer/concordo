#ifndef USUARIO_H
#define USUARIO_H
#include <string>

using namespace std;

class Usuario {
private:
	int id;
	string nome;
	string email;
	string senha;

public:
	/* @brief Constructor.
	 * @param id User's ID.
	 * @param nome User's name.
	 * @param email User's email.
	 * @param senha User's password.
	 */
	Usuario(int id, string nome, string email, string senha);

	/* @brief Getters for attributes.
	 * @return Value of corresponding attribute.
	 */
	int get_id();
	string get_nome();
	string get_email();

	/* @brief Checks if a given password matches the user's password.
	 * @param senha Password to be tested.
	 * @return True if passwords match; false if they don't.
	 */
	bool igual_senha(string senha);
};

#endif

