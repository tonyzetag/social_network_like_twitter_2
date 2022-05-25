#include "usuario_twitter.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <cstdio>
#include <cstdlib>

#ifdef __LINUX__
#include <tr1/array>
#else
#include <array>
#endif // !

using namespace std;

namespace bblProgII {
	//------------------------------------------------------------------
	// CONSTRUCTORES Y DESTRUCTORES
	UsuarioTwitter::UsuarioTwitter() : id_usuario(""), tweets(), siguiendo(), seguidores(), menciones() {
		tweets.num_tweets = 0;
		siguiendo.num_usuarios = 0;
		seguidores.num_usuarios = 0;
		// Parte Opcional
		menciones.num_menciones = 0;
	}

	UsuarioTwitter::UsuarioTwitter(const std::string &id) {
		id_usuario = id;
		tweets.num_tweets = 0;
		siguiendo.num_usuarios = 0;
		seguidores.num_usuarios = 0;
		// Parte Opcional
		menciones.num_menciones = 0;
	}

	UsuarioTwitter::UsuarioTwitter(const UsuarioTwitter &otro_usuario)
		: id_usuario(otro_usuario.id_usuario), tweets(), siguiendo(), seguidores(), menciones()
	{
		// Copiamos la clase tweets
		tweets = otro_usuario.tweets;

		// Copiamos el listado de seguidores
		seguidores.num_usuarios = otro_usuario.seguidores.num_usuarios;
		for (unsigned i = 0; i < seguidores.num_usuarios; i++) {
			seguidores.listado[i] = otro_usuario.seguidores.listado[i];
		}

		// Copiamos el listado de siguiendo
		siguiendo.num_usuarios = otro_usuario.siguiendo.num_usuarios;
		for (unsigned i = 0; i < siguiendo.num_usuarios; i++) {
			siguiendo.listado[i] = otro_usuario.siguiendo.listado[i];
		}

		// Parte Opcional, copiamos el numero de menciones
		menciones.num_menciones = otro_usuario.menciones.num_menciones;
		for (unsigned i = 0; i < menciones.num_menciones; i++) {
			menciones.listado[i] = otro_usuario.menciones.listado[i];
		}
	}

	UsuarioTwitter & UsuarioTwitter::operator=(const UsuarioTwitter &otro_usuario) {

		if (this != &otro_usuario) {

			this->~UsuarioTwitter();

			id_usuario = otro_usuario.id_usuario;
			// Copiamos la clase tweets
			tweets = otro_usuario.tweets;

			// Copiamos el listado de seguidores
			seguidores.num_usuarios = otro_usuario.seguidores.num_usuarios;
			for (unsigned i = 0; i < seguidores.num_usuarios; i++) {
				seguidores.listado[i] = otro_usuario.seguidores.listado[i];
			}

			// Copiamos el listado de siguiendo
			siguiendo.num_usuarios = otro_usuario.siguiendo.num_usuarios;
			for (unsigned i = 0; i < siguiendo.num_usuarios; i++) {
				siguiendo.listado[i] = otro_usuario.siguiendo.listado[i];
			}

			// Parte Opcional, copiamos el numero de menciones
			menciones.num_menciones = otro_usuario.menciones.num_menciones;
			for (unsigned i = 0; i < menciones.num_menciones; i++) {
				menciones.listado[i] = otro_usuario.menciones.listado[i];
			}
		}
		return *this;
	}

	UsuarioTwitter::~UsuarioTwitter() {};

	//------------------------------------------------------------------
	// MÉTODOS DE CONSULTA

	string UsuarioTwitter::obtener_id() const {
		return id_usuario;
	}

	void UsuarioTwitter::obtener_seguidores(Usuarios &lista_seg) const {
		lista_seg = seguidores;
	}

	void UsuarioTwitter::obtener_siguiendo(Usuarios &lista_sig) const {
		lista_sig = siguiendo;
	}

	void UsuarioTwitter::obtener_tweets(Tweets &lista_tweets) const {
		lista_tweets = tweets;
	}

	bool UsuarioTwitter::me_sigue(const string &otro_usuario) const {
		bool mismo_usuario;
		// Primero busco la posición donde debería estar
		unsigned pos = buscar_usuario(seguidores, otro_usuario);
		// Si es el mismo usuario devuelve true, si no, false
		if (seguidores.listado[pos] == otro_usuario) {
			mismo_usuario = true;
		}
		else {
			mismo_usuario = false;
		}
		return mismo_usuario;
	}

	bool UsuarioTwitter::estoy_siguiendo(const string &otro_usuario) const {
		bool mismo_usuario;
		// Primero busco la posición donde debería estar
		unsigned pos = buscar_usuario(siguiendo, otro_usuario);
		// Si es el mismo usuario devuelve true, si no, false
		if (siguiendo.listado[pos] == otro_usuario) {
			mismo_usuario = true;
		}
		else {
			mismo_usuario = false;
		}
		return mismo_usuario;
	}

	unsigned UsuarioTwitter::num_seguidores() const {
		return seguidores.num_usuarios;
	}

	unsigned UsuarioTwitter::num_siguiendo() const {
		return siguiendo.num_usuarios;
	}

	unsigned UsuarioTwitter::num_tweets() const {
		return tweets.num_tweets;
	}

	void UsuarioTwitter::imprimir_seguidores(unsigned num_imprime) const {
		// PRECONDICIÓN: num_imprime <= num_seguidores
		assert (num_imprime <= seguidores.num_usuarios);
		// Si num_imprime == 0, imprime todos los seguidores
		if (num_imprime == 0) {
			for (unsigned i = 0; i < seguidores.num_usuarios; i++) {
				cout << i + 1 << ": " << seguidores.listado[i] << endl;
			}
		}
		// Si num_imprime != 0, imprime "num_imprime" seguidores
		else {
			for (unsigned i = 0; i < num_imprime; i++) {
				cout << i + 1 << ": " << seguidores.listado[i] << endl;
			}
		}
	}

	void UsuarioTwitter::imprimir_siguiendo(unsigned num_imprime) const {
		// PRECONDICIÓN: num_imprime <= num_siguiendo
		assert (num_imprime <= siguiendo.num_usuarios);
		// Si num_imprime == 0, imprime todos los seguidos
		if (num_imprime == 0) {
			for (unsigned i = 0; i < siguiendo.num_usuarios; i++) {
				cout << i + 1 << ": " << siguiendo.listado[i] << endl;
			}
		}
		// Si num_imprime != 0, imprime "num_imprime" seguidores
		else {
			for (unsigned i = 0; i < num_imprime; i++) {
				cout << i + 1 << ": " << siguiendo.listado[i] << endl;
			}
		}
	}

	void UsuarioTwitter::imprimir_tweets(unsigned num_imprime) const {
		// PRECONDICIÓN: num_imprime <= num_tweets
		assert (num_imprime <= tweets.num_tweets);
		// Si num_imprime == 0, imprime todos los tweets del usuario.
		if (num_imprime == 0) {
			for (unsigned i = 0; i < tweets.num_tweets; i++) {
				cout <<
					tweets.listado[i].fecha_hora.dia << " " <<
					tweets.listado[i].fecha_hora.mes << " " <<
					tweets.listado[i].fecha_hora.anyo << " " <<
					tweets.listado[i].fecha_hora.hora << " " <<
					tweets.listado[i].fecha_hora.minuto << " " <<
					tweets.listado[i].fecha_hora.segundo << " " <<
					tweets.listado[i].tweet << endl;
			}
		}
		// Si no, imprime el número de tweets que se indica.
		else if (num_imprime > 0) {
			for (unsigned i = (tweets.num_tweets) - num_imprime; i < tweets.num_tweets; i++) {
				cout <<
					tweets.listado[i].fecha_hora.dia << " " <<
					tweets.listado[i].fecha_hora.mes << " " <<
					tweets.listado[i].fecha_hora.anyo << " " <<
					tweets.listado[i].fecha_hora.hora << " " <<
					tweets.listado[i].fecha_hora.minuto << " " <<
					tweets.listado[i].fecha_hora.segundo << " " <<
					tweets.listado[i].tweet << endl;
			}
		}
	}

	void UsuarioTwitter::guardar_seguidores(const string &nom_fic, Resultado &res) const {
		// Variables
		ofstream fichero;
		// Abrimos
		fichero.open((nom_fic + ".seg").c_str());
		// Comprobación
		if (!fichero.fail() && (this->num_seguidores() > 0)) {
			unsigned n = 0;
			fichero << seguidores.listado[n] << std::endl;
			while (!fichero.fail() && n < seguidores.num_usuarios - 1)
			{
				n++;
				fichero << seguidores.listado[n] << std::endl;
			}
		}
		res = (!fichero.fail()) ? OK : FIC_ERROR;
		// Cerrar
		fichero.close();
	}

	void UsuarioTwitter::guardar_seguiendo(const string &nom_fic, Resultado &res) const {
		// Variables
		ofstream fichero;
		// Abrimos
		fichero.open((nom_fic + ".sig").c_str());
		// Comprobación
		if (!fichero.fail() && (this->num_siguiendo() > 0)) {
			unsigned n = 0;
			fichero << siguiendo.listado[n] << std::endl;
			while (!fichero.fail() && n < siguiendo.num_usuarios - 1)
			{
				n++;
				fichero << siguiendo.listado[n] << std::endl;
			}
		}
		res = (!fichero.fail()) ? OK : FIC_ERROR;
		// Cerrar
		fichero.close();
	}

	void UsuarioTwitter::guardar_tweets(const string &nom_fic, Resultado &res) const {
		// Variables
		ofstream fichero;
		Tweet nuevo;
		// Abrimos
		fichero.open((nom_fic + ".twt").c_str());
		// Comprobación
		if (!fichero.fail() && (this->num_tweets() > 0)) {
			unsigned n = 0;
			nuevo = tweets.listado[n];
			fichero <<
				nuevo.fecha_hora.dia << " " <<
				nuevo.fecha_hora.mes << " " <<
				nuevo.fecha_hora.anyo << " " <<
				nuevo.fecha_hora.hora << " " <<
				nuevo.fecha_hora.minuto << " " <<
				nuevo.fecha_hora.segundo << " " <<
				nuevo.tweet << std::endl;
			while (!fichero.fail() && n < tweets.num_tweets - 1)
			{
				n++;
				nuevo = tweets.listado[n];
				fichero <<
					nuevo.fecha_hora.dia << " " <<
					nuevo.fecha_hora.mes << " " <<
					nuevo.fecha_hora.anyo << " " <<
					nuevo.fecha_hora.hora << " " <<
					nuevo.fecha_hora.minuto << " " <<
					nuevo.fecha_hora.segundo << " " <<
					nuevo.tweet << std::endl;
			}
		}
		res = (!fichero.fail()) ? OK : FIC_ERROR;
		// Cerrar
		fichero.close();
	}

	void UsuarioTwitter::guardar_todo(const string &nom_fic_seguidores,
		const string &nom_fic_siguiendo,
		const string &nom_fic_tweets,
		const string &nom_fic_menciones,
		Resultado &res_seguidores,
		Resultado &res_siguiendo,
		Resultado &res_tweets,
		Resultado &res_menciones) const
	{
		// Usamos las funciones de guardado de cada uno
		guardar_seguidores(nom_fic_seguidores, res_seguidores);
		guardar_seguiendo(nom_fic_siguiendo, res_siguiendo);
		guardar_tweets(nom_fic_tweets, res_tweets);
		guardar_meciones(nom_fic_menciones, res_menciones);

	}

	//------------------------------------------------------------------
	// MÉTODOS DE ACTUALIZACIÓN
	void UsuarioTwitter::establecer_id(const string &nuevo_id) {
		id_usuario = nuevo_id;
	}

	void UsuarioTwitter::nuevo_seguidor(const string &nuevo, Resultado &res) {
		// Posición en la que debería de estar "nuevo"
		unsigned pos = buscar_usuario(seguidores, nuevo);
		// Comprobación de que no existe
		bool existe = (seguidores.listado[pos] == nuevo) ? true : false;
		// Comprobación de lista llena
		bool llena = (seguidores.num_usuarios == MAX_USUARIOS) ? true : false;
		// Asignación de valor a res
		if (existe) {
			res = YA_EXISTE;
		}
		else if (llena) {
			res = LISTA_LLENA;
		}
		else {
			insertar_usuario_pos(seguidores, pos, nuevo);
			res = OK;
		}
	}

	void UsuarioTwitter::nuevo_siguiendo(const string &nuevo, Resultado &res) {
		// Posición en la que debería de estar "nuevo"
		unsigned pos = buscar_usuario(siguiendo, nuevo);
		// Comprobación de que no existe
		bool existe = (siguiendo.listado[pos] == nuevo) ? true : false;
		// Comprobación de lista llena
		bool llena = (siguiendo.num_usuarios == MAX_USUARIOS) ? true : false;
		// Asignación de valor a res
		if (existe) {
			res = YA_EXISTE;
		}
		else if (llena) {
			res = LISTA_LLENA;
		}
		else {
			insertar_usuario_pos(siguiendo, pos, nuevo);
			res = OK;
		}
	}

	void UsuarioTwitter::nuevo_tweet(const Tweet &nuevo, Resultado &res) {
		// Constante, máxima longitud de tweet
		const unsigned MAX_LONG_TWEET = 140;
		// Comprobación de lista llena
		bool llena = (tweets.num_tweets == MAX_TWEETS) ? true : false;
		// Asignación de valor a res
		res = (llena) ? LISTA_LLENA : OK;
		// Si todo va bien, inserta nuevo tweet (140 caracteres)
		if (res == OK) {
			Tweet formateado = nuevo;
			tweets.num_tweets++;
			if (formateado.tweet.length() > MAX_LONG_TWEET) {
				formateado.tweet.resize(MAX_LONG_TWEET);
			}
			tweets.listado[tweets.num_tweets - 1] = formateado;
		}
	}

	void UsuarioTwitter::eliminar_seguidor(const string &usuario, Resultado &res) {
		// Si sigo a ese usuario
		if (me_sigue(usuario)) {
			res = OK;
			unsigned pos;
			pos = buscar_usuario(seguidores, usuario);
			// Esliminarlo y reordenar
			for (unsigned i = pos; i < seguidores.num_usuarios - 1; i++) {
				seguidores.listado[i] = seguidores.listado[i + 1];
			}
			seguidores.num_usuarios--;
		}
		// Si no lo sigo
		else {
			res = NO_EXISTE;
		}
	}

	void UsuarioTwitter::eliminar_siguiendo(const string &usuario, Resultado &res) {
		// Si sigo a ese usuario
		if (estoy_siguiendo(usuario)) {
			res = OK;
			unsigned pos;
			pos = buscar_usuario(siguiendo, usuario);
			// Esliminarlo y reordenar
			for (unsigned i = pos; i < siguiendo.num_usuarios - 1; i++) {
				siguiendo.listado[i] = siguiendo.listado[i + 1];
			}
			siguiendo.num_usuarios--;
		}
		// Si no lo sigo
		else {
			res = NO_EXISTE;
		}
	}

	void UsuarioTwitter::cargar_seguidores(const string &nom_fic, Resultado &res) {
		// Variables
		ifstream fichero;
		string seguidor;
		string extension = ".seg";
		// Abrir fichero
		fichero.open((nom_fic + extension).c_str());
		// Si no falla, leer los usuarios
		if (!fichero.fail()) {
			getline(fichero, seguidor);
			while (!fichero.fail() && res == OK) {
				nuevo_seguidor(seguidor, res);
				getline(fichero, seguidor);
			}
		}
		// Si el fichero ha llegado al final, todo correcto
		res = (fichero.eof()) ? OK : FIC_ERROR;
		// Cerramos
		fichero.close();
	}

	void UsuarioTwitter::cargar_seguiendo(const string &nom_fic, Resultado &res) {
		// Variables
		ifstream fichero;
		string siguiendo;
		string extension = ".sig";
		// Abrir fichero
		fichero.open((nom_fic + extension).c_str());
		// Si no falla, leer los usuarios
		if (!fichero.fail()) {
			getline(fichero, siguiendo);
			while (!fichero.fail() && res == OK) {
				nuevo_siguiendo(siguiendo, res);
				getline(fichero, siguiendo);
			}
		}
		// Si el fichero ha llegado al final, todo correcto
		res = (fichero.eof()) ? OK : FIC_ERROR;
		// Cerramos
		fichero.close();
	}

	void UsuarioTwitter::cargar_tweets(const string &nom_fic, Resultado &res) {
		// Variables
		ifstream fichero;
		Tweet nuevo;
		string extension = ".twt";
		// Abrir fichero
		fichero.open((nom_fic + extension).c_str());
		// Si no falla, leer los usuarios
		if (!fichero.fail()) {
			fichero >>
				nuevo.fecha_hora.dia >>
				nuevo.fecha_hora.mes >>
				nuevo.fecha_hora.anyo >>
				nuevo.fecha_hora.hora >>
				nuevo.fecha_hora.minuto >>
				nuevo.fecha_hora.segundo;
				if (!fichero.fail()) {
					getline(fichero, nuevo.tweet);
				}
			while (!fichero.fail() && res == OK && !fichero.eof()) {
				nuevo_tweet(nuevo, res);
				fichero >>
					nuevo.fecha_hora.dia >>
					nuevo.fecha_hora.mes >>
					nuevo.fecha_hora.anyo >>
					nuevo.fecha_hora.hora >>
					nuevo.fecha_hora.minuto >>
					nuevo.fecha_hora.segundo;
				if (!fichero.fail()) {
					getline(fichero, nuevo.tweet);
				}
			}
		}
		// Si el fichero ha llegado al final, todo correcto
		res = (fichero.eof()) ? OK : FIC_ERROR;
		// Cerramos
		fichero.close();
	}

	void UsuarioTwitter::cargar_todo(const std::string &nom_fic_seguidores,
		const string &nom_fic_siguiendo,
		const string &nom_fic_tweets,
		const string &nom_fic_menciones,
		Resultado & res_seguidores,
		Resultado & res_siguiendo,
		Resultado & res_tweets,
		Resultado & res_menciones)
	{
		cargar_seguidores(nom_fic_seguidores, res_seguidores);
		cargar_seguiendo(nom_fic_siguiendo, res_siguiendo);
		cargar_tweets(nom_fic_tweets, res_tweets);
		cargar_menciones(nom_fic_menciones, res_menciones);
	}

	//------------------------------------------------------------------
	// PARTE OPCIONAL:

	void UsuarioTwitter::obtener_menciones(Menciones &men) const {
		men.num_menciones = menciones.num_menciones;
		for (unsigned i = 0; i < menciones.num_menciones; i++)	{
			men.listado[i].id_tweet = menciones.listado[i].id_tweet;
			men.listado[i].id_usuario = menciones.listado[i].id_usuario;
		}
	}

	unsigned UsuarioTwitter::num_menciones() const {
		return menciones.num_menciones;
	}

	void UsuarioTwitter::imprimir_menciones(unsigned num_imprime) const {
		bool ok = (num_imprime <= menciones.num_menciones) ? true : false;
		if (ok && num_imprime == 0) {
			for (unsigned i = 0; i < menciones.num_menciones; i++) {
				cout << "Id tweet:" << menciones.listado[i].id_tweet << ", usuario: " << menciones.listado[i].id_usuario << endl;
			}
		}
		else if (ok && num_imprime != 0) {
			for (unsigned i = 0; i < num_imprime; i++) {
				cout << "Id tweet:" << menciones.listado[i].id_tweet << ", usuario: " << menciones.listado[i].id_usuario << endl;
			}
		}
	}

	void UsuarioTwitter::obtener_menciones(const string &con_usuario, Menciones &men) const {
		// Variables
		men.num_menciones = 0;
		bool cabe;
		string cadena, usuario;
		unsigned pos = 0;
		// Revisar en cada tweet las menciones
		for (unsigned i = 0; i < tweets.num_tweets; i++) {
			cabe = (men.num_menciones < MAX_MENCIONES) ? true : false;
			cadena = tweets.listado[i].tweet + ' ';
			while (cabe && (cadena.find('@') < cadena.length())) {
				// Primero buscar la cadena desde @ hasta el espacio siguiente
				cadena = cadena.substr(cadena.find('@'));
				if (cadena.find(',') < cadena.find(' ')) {
					pos = cadena.find(',');
				}
				else {
					pos = cadena.find(' ');
				}
				usuario = cadena.substr(1, pos - 1);
				// Ahora que tenemos la cadena usuario se la asignamos a men si coincide el usuario
				if (usuario == con_usuario) {
					men.listado[men.num_menciones].id_usuario = id_usuario;
					men.listado[men.num_menciones].id_tweet = i;
					men.num_menciones++;
				}
				// Pasamos al siguiente caracter
				cadena = cadena.substr(1);
			}
		}
	}

	void UsuarioTwitter::nueva_mencion(const Mencion &mencion, Resultado &res) {

		res = (menciones.num_menciones < MAX_MENCIONES) ? OK : LISTA_LLENA;
		if (res == OK) {
			for (unsigned i = 0; i < menciones.num_menciones; i++) {
				if ((menciones.listado[i].id_tweet == mencion.id_tweet) && (menciones.listado[i].id_usuario == mencion.id_usuario)) {
					res = YA_EXISTE;
				}
			}
		}
		if (res == OK) {
			menciones.listado[menciones.num_menciones].id_tweet = mencion.id_tweet;
			menciones.listado[menciones.num_menciones].id_usuario = mencion.id_usuario;
			menciones.num_menciones++;
		}
	}

	void UsuarioTwitter::cargar_menciones(const string &nom_fic, Resultado &res) {
		// Variables
		ifstream fichero;
		unsigned n = 0;
		string extension = ".men";
		// Abrimos fichero
		fichero.open((nom_fic + extension).c_str());
		// Si no falla, leemos
		if (!fichero.fail()) {
			fichero >> std::ws;
			fichero >> menciones.listado[n].id_usuario;
			fichero >> menciones.listado[n].id_tweet;
			while (!fichero.fail() && n < MAX_MENCIONES && fichero) {
				n++;
				menciones.num_menciones = n;
				fichero >> std::ws;
				fichero >> menciones.listado[n].id_usuario;
				fichero >> menciones.listado[n].id_tweet;
			}
			// Comprobamos que todo esté correcto
			res = (n == MAX_MENCIONES) ? LISTA_LLENA : OK;
			if (res == OK) {
				res = (fichero.eof()) ? OK : FIC_ERROR;
			}
		}
		fichero.close();
	}

	void UsuarioTwitter::guardar_meciones(const string &nom_fic, Resultado &res) const {
		// Variables
		ofstream fichero;
		// Abrimos fichero
		fichero.open((nom_fic + ".men").c_str());
		// Si no falla, guardar
		if (!fichero.fail() && this->menciones.num_menciones > 0) {
			for (unsigned i = 0; i < menciones.num_menciones - 1; i++) {
				fichero << menciones.listado[i].id_usuario << " " << menciones.listado[i].id_tweet << endl;
			}
			fichero << menciones.listado[menciones.num_menciones - 1].id_usuario << " " <<  menciones.listado[menciones.num_menciones - 1].id_tweet;
		}
		res = (fichero.fail()) ? FIC_ERROR : OK;
		// Cerramos fichero
		fichero.close();
	}

	//------------------------------------------------------------------
	// PARTE OPCIONAL AÑADIDAS:

	void UsuarioTwitter::obtener_lista_usuarios_mencionados(Usuarios &lista) const {
		// Variables
		Menciones men;
		men.num_menciones = 0;
		bool cabe, existe = false;
		string cadena, usuario;
		unsigned pos = 0;
		lista.num_usuarios = 0;

		// Revisar en cada tweet las menciones
		for (unsigned i = 0; i < tweets.num_tweets; i++) {
			cabe = (men.num_menciones < MAX_MENCIONES) ? true : false;
			cadena = tweets.listado[i].tweet + ' ';
			while (cabe && (cadena.find('@') < cadena.length())) {
				// Primero buscar la cadena desde @ hasta el espacio siguiente
				cadena = cadena.substr(cadena.find('@'));
				existe = false;
				if (cadena.find(',') < cadena.find(' ')) {
					pos = cadena.find(',');
				}
				else {
					pos = cadena.find(' ');
				}
				usuario = cadena.substr(1, pos - 1);
				// Ahora que tenemos la cadena usuario se la asignamos a men si coincide el usuario
				for (unsigned j = 0; j < lista.num_usuarios; j++) {
					if (usuario == lista.listado[j]) {
						existe = true;
					}
				}
				if (existe == false) {
					lista.listado[lista.num_usuarios] = usuario;
					lista.num_usuarios++;
				}
				men.listado[men.num_menciones].id_usuario = usuario;
				men.listado[men.num_menciones].id_tweet = i;
				men.num_menciones++;

				// Pasamos al siguiente caracter
				cadena = cadena.substr(1);
			}
		}
	}

	void UsuarioTwitter::obtener_lista_usuarios_que_te_han_mencionado(Usuarios &lista) const {
		// Variables
		string usuario;
		bool existe = false;
		// Inicialización
		lista.num_usuarios = 0;
		//
		for (unsigned i = 0; i < menciones.num_menciones; i++) {
			usuario = menciones.listado[i].id_usuario;
			for (unsigned j = 0; j < lista.num_usuarios; j++) {
				if (usuario == lista.listado[j]) {
					existe = true;
				}
			}
			if (existe == false) {
				lista.listado[lista.num_usuarios] = usuario;
				lista.num_usuarios++;
			}
			existe = false;
		}
	}

	void UsuarioTwitter::eliminar_menciones() {
		menciones.num_menciones = 0;
	}

	//------------------------------------------------------------------
	// MÉTODOS PRIVADOS:

	unsigned UsuarioTwitter::buscar_usuario(const Usuarios &usuarios, const string &user) const {
		// Variables
		unsigned pos = 0;
		bool fin = false;
		// Bucle hasta encontrar la posición
		while (fin == false && pos <= usuarios.num_usuarios) {
			// Si estamos en la ultima posición finaliza bucle
			if (pos == usuarios.num_usuarios) {
				fin = true;
			}
			// Si el usuario actual es menor que el nuevo usuario, está antes por lo que sigue iterando
			if ((fin == false) && (usuarios.listado[pos] < user)) {
				pos++;
			}
			// Si el usuario actual es mayor o igual que el nuevo usuario, posición encontrada
			else if ((fin == false) && (usuarios.listado[pos] >= user)) {
				fin = true;
			}
		}
		return pos;
	}

	void UsuarioTwitter::insertar_usuario_pos(Usuarios &usuarios, unsigned pos, const string &usuario) {
		// PRECONDICIÓN: el usuario cabe en la lista
		bool cabe = (usuarios.num_usuarios < MAX_USUARIOS) ? true : false;
		// PRECONDICIÓN: la posición es correcta
		bool posicion_correcta = (pos == buscar_usuario(usuarios, usuario)) ? true : false;
		// Si cumple, inserta un usuario en la lista en la posición indicada
		if (cabe && posicion_correcta) {
			// Añade 1 a la lista
			usuarios.num_usuarios++;
			// Bucle de reordenación desde el ultimo hasta llegar a pos
			for (unsigned i = usuarios.num_usuarios; i > pos; i--) {
				usuarios.listado[i] = usuarios.listado[i - 1];
			}
			// Y para finalizar, añadimos en la posición el usuario
			usuarios.listado[pos] = usuario;
		}
	}

	void UsuarioTwitter::eliminar_usuario_pos(Usuarios &usuarios, unsigned pos) {
		// PRECONDICIÓN: la posición es correcta
		bool posicion_correcta = (pos >= 0 && pos < usuarios.num_usuarios) ? true : false;
		// Si todo va bien, eliminar usuario
		if (posicion_correcta) {
			// Elimino el usuario pisandolo con el siguiente
			for (unsigned i = pos; i < usuarios.num_usuarios - 1; i++) {
				usuarios.listado[i] = usuarios.listado[i + 1];
			}
			// Quito 1 de la cuenta de la lista
			usuarios.num_usuarios--;
		}
	}
}

