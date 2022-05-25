#include "twitter.hpp"
#include <iostream>
#include <string>
#include <cassert>
#include <fstream>

using namespace std;

namespace bblProgII {
	Twitter::Twitter()
		: usuarios(nullptr), usuario_conectado (nullptr) { }

	// Constructor de copia de la clase
	Twitter::Twitter(const Twitter &otro_twitter)
		: usuarios(), usuario_conectado() {
		// proceso copia de otro_twitter a nuestro twitter (utilizando nuestro metodo privado)
		PtrUsuario ptr = otro_twitter.usuarios;
		while (ptr != nullptr) {
			insertar_usuario(ptr->usuario);
			ptr = ptr->sig;
		}
		ptr = otro_twitter.usuario_conectado;
		while (ptr != nullptr) {
			insertar_usuario(ptr->usuario);
			ptr = ptr->sig;
		}
	}

	// Operador de asignación (opcional)
	Twitter & Twitter::operator=(const Twitter &otro_twitter) {
		if (this != &otro_twitter) {
			// Borrar lista
			borrar_todo();
			// Duplicar lista
			PtrUsuario ptr = otro_twitter.usuarios;
			while (ptr != nullptr) {
				insertar_usuario(ptr->usuario);
				ptr = ptr->sig;
			}
			ptr = otro_twitter.usuario_conectado;
			while (ptr != nullptr) {
				insertar_usuario(ptr->usuario);
				ptr = ptr->sig;
			}
		}

		return *this;
	}

	// Destructor de la clase.
	Twitter::~Twitter() {
		borrar_todo();
	}

	// Devuelve el número de usuarios de la red social
	unsigned Twitter::num_usuarios() const {
		// variables
		unsigned sol = 0;
		// Caso 1.- La lista está vacía
		if (usuarios == nullptr) {
			sol = 0;
		}
		// Caso 2.- La lista no está vacía
		else {
			PtrUsuario ptr; // Creamos el puntero
			ptr = usuarios; // ptr apunta a la lista de usuarios
			while (ptr != nullptr) { // Mientras ptr no apunte a null suma nodos
				sol++;
				ptr = ptr->sig;
			}
		}
		return sol;
	}

	// Devuelve el id del usuario actualmente conectado. Si no hay usuario
	// conectado, devuelve una cadena vacía
	string Twitter::usuario_actual() const {
		// variables
		string cadena;
		// Caso 1.- Usuario conectado está vacío
		if (usuario_conectado == nullptr) {
			cadena = "";
		}
		// caso 2.- Existe usuario conectado
		else {
			cadena = usuario_conectado->usuario.obtener_id();
		}
		return cadena;
	}

	//------------------------------------------------------------------
	// PARA EL USUARIO ACTUAL. |
	// ------------------------|
	//
	// Devuelve los seguidores del usuario conectado
	// Si no hay usuario conectado, los métodos
	// devuelven false a través de 'conectado'. Si no, devuelven true.
	// Devuelve la lista de seguidores
	void Twitter::obtener_seguidores(Usuarios &lista_seg, bool &conectado) const {
		// caso 1.- No hay un usuario conectado
		if (usuario_conectado == nullptr) {
			conectado = false;
		}
		// caso 2.- Existe un usuario conectado
		else {
			conectado = true;
			usuario_conectado->usuario.obtener_seguidores(lista_seg);
		}
	}

	// Devuelve la lista de usuarios a los que se sigue el usuario conectado
	void Twitter::obtener_siguiendo(Usuarios &lista_sig, bool &conectado) const {
		// caso 1.- No hay un usuario conectado
		if (usuario_conectado == nullptr) {
			conectado = false;
		}
		// caso 2.- Existe un usuario conectado
		else {
			conectado = true;
			usuario_conectado->usuario.obtener_siguiendo(lista_sig);
		}
	}

	// Devuelve la lista de tweets del usuario conectado
	void Twitter::obtener_tweets(Tweets &lista_tweets, bool &conectado) const {
		// caso 1.- No hay un usuario conectado
		if (usuario_conectado == nullptr) {
			conectado = false;
		}
		// caso 2.- Existe un usuario conectado
		else {
			conectado = true;
			usuario_conectado->usuario.obtener_tweets(lista_tweets);
		}
	}

	// Devuelve la lista de menciones (menciones) al usuario conectado
	void Twitter::obtener_menciones(Menciones &lista_int, bool &conectado) const {
		// caso 1.- No hay un usuario conectado
		if (usuario_conectado == nullptr) {
			conectado = false;
		}
		// caso 2.- Existe un usuario conectado
		else {
			conectado = true;
			usuario_conectado->usuario.obtener_menciones(lista_int);
		}
	}

	// Indica si un determinado usuario es seguidor del usuario conectado
	void Twitter::me_sigue(const std::string &otro_usuario, bool &mesigue, bool &conectado) const {
		// caso 1.- No hay un usuario conectado
		if (usuario_conectado == nullptr) {
			conectado = false;
		}
		// caso 2.- Existe un usuario conectado
		else {
			conectado = true;
			mesigue = usuario_conectado->usuario.me_sigue(otro_usuario);
		}
	}

	// Indica si este usuario conectado está siguiendo a otro
	void Twitter::estoy_siguiendo(const std::string &otro_usuario, bool &sigo, bool &conectado) const {
		// caso 1.- No hay un usuario conectado
		if (usuario_conectado == nullptr) {
			conectado = false;
		}
		// caso 2.- Existe un usuario conectado
		else {
			conectado = true;
			sigo = usuario_conectado->usuario.estoy_siguiendo(otro_usuario);
		}
	}

	// Devuelve el número de seguidores del usuario conectado
	void Twitter::num_seguidores(unsigned &n_mesiguen, bool &conectado) const {
		// caso 1.- No hay un usuario conectado
		if (usuario_conectado == nullptr) {
			conectado = false;
		}
		// caso 2.- Existe un usuario conectado
		else {
			conectado = true;
			n_mesiguen = usuario_conectado->usuario.num_seguidores();
		}
	}

	// Devuelve el número de usuarios a los que sigue el usuario conectado
	void Twitter::num_siguiendo(unsigned &n_siguiendo, bool &conectado) const {
		// caso 1.- No hay un usuario conectado
		if (usuario_conectado == nullptr) {
			conectado = false;
		}
		// caso 2.- Existe un usuario conectado
		else {
			conectado = true;
			n_siguiendo = usuario_conectado->usuario.num_siguiendo();
		}
	}

	// Devuelve el número de tweets del usuario
	void Twitter::num_tweets(unsigned &n_tweets, bool &conectado) const {
		// caso 1.- No hay un usuario conectado
		if (usuario_conectado == nullptr) {
			conectado = false;
		}
		// caso 2.- Existe un usuario conectado
		else {
			conectado = true;
			n_tweets = usuario_conectado->usuario.num_tweets();
		}
	}

	// Devuelve el número de menciones
	void Twitter::num_menciones(unsigned &n_menciones, bool &conectado) const {
		// caso 1.- No hay un usuario conectado
		if (usuario_conectado == nullptr) {
			conectado = false;
		}
		// caso 2.- Existe un usuario conectado
		else {
			conectado = true;
			n_menciones = usuario_conectado->usuario.num_menciones();
		}
	}

	// Imprime por pantalla la lista de seguidores
	// Si num_imprime == 0, imprime todos los seguidores.
	// PRECONDICIÓN: num_imprime <= num_seguidores
	void Twitter::imprimir_seguidores(unsigned num_imprime, bool &conectado) const {
		// caso 1.- No hay un usuario conectado
		if (usuario_conectado == nullptr) {
			conectado = false;
		}
		// caso 2.- Existe un usuario conectado
		else {
			conectado = true;
			// Precondición
			assert(num_imprime <= usuario_conectado->usuario.num_seguidores());
			usuario_conectado->usuario.imprimir_seguidores(num_imprime);
		}

	}

	// Imprime por pantalla la lista de usuarios a los que sigue
	// Si num_imprime == 0, imprime todos los usuarios a los que sigue.
	// PRECONDICIÓN: num_imprime <= num_siguiendo
	void Twitter::imprimir_siguiendo(unsigned num_imprime, bool &conectado) const {
		// caso 1.- No hay un usuario conectado
		if (usuario_conectado == nullptr) {
			conectado = false;
		}
		// caso 2.- Existe un usuario conectado
		else {
			conectado = true;
			// Precondición
			assert(num_imprime <= usuario_conectado->usuario.num_siguiendo());
			usuario_conectado->usuario.imprimir_siguiendo(num_imprime);
		}
	}

	// Imprime por pantalla la lista de tweets
	// Si num_imprime == 0, imprime todos los tweets del usuario.
	// PRECONDICIÓN: num_imprime <= num_tweets
	void Twitter::imprimir_tweets(unsigned num_imprime, bool &conectado) const {
		// caso 1.- No hay un usuario conectado
		if (usuario_conectado == nullptr) {
			conectado = false;
		}
		// caso 2.- Existe un usuario conectado
		else {
			conectado = true;
			// Precondición
			assert(num_imprime <= usuario_conectado->usuario.num_tweets());
			usuario_conectado->usuario.imprimir_tweets(num_imprime);
		}
	}

	// Imprime por pantalla la lista de menciones
	// Si num_imprime == 0, imprime todas las menciones.
	// PRECONDICIÓN: num_imprime <= num_menciones
	void Twitter::imprimir_menciones(unsigned num_imprime, bool &conectado) const {
		// caso 1.- No hay un usuario conectado
		if (usuario_conectado == nullptr) {
			conectado = false;
		}
		// caso 2.- Existe un usuario conectado
		else {
			conectado = true;
			// Precondición
			assert(num_imprime <= usuario_conectado->usuario.num_menciones());
			usuario_conectado->usuario.imprimir_menciones(num_imprime); // en la función ya viene la condición dada de num_imprime
		}
	}

	// Modifica el identificador del usuario actualmente conectado
	// Devuelve 'true' si ha sido posible modificar el usuario
	// actualmente conectado.
	// Deben modificarse la lista de seguidores y siguiendo de los
	// demás usuarios de la red para actualizarlas con el nuevo
	// identificador del usuario conectado
	void Twitter::establecer_id(const std::string &nuevo_id, bool &conectado) {
		// caso 1.- No hay un usuario conectado
		if (usuario_conectado == nullptr) {
			conectado = false;
		}
		// caso 2.- Existe un usuario conectado
		else {
			conectado = true;
			// Obtengo el id antiguo
			string antiguo_id = usuario_actual();
			// modifico el nuevo ide del usuario actuaa conectado
			usuario_conectado->usuario.establecer_id(nuevo_id);
			// recorro la lista de usuarios modificando el seguidor o seguidores
			Resultado res_seg, res_sig;
			PtrUsuario ptr = usuarios; // puntero a la lista de usuarios
			while (ptr != nullptr) {
				if (ptr->usuario.obtener_id() != antiguo_id) { // si es diferente el usuario actual busco el antiguo id
					if (ptr->usuario.estoy_siguiendo(antiguo_id)) { // si existe elimino el antiguo y añado el nuevo
						ptr->usuario.eliminar_siguiendo(antiguo_id, res_sig);
						if (res_sig != OK) {
							cout << "Error al eliminar siguiendo: " << antiguo_id << " del usuario " << ptr->usuario.obtener_id() << endl;
						}
						else {
							ptr->usuario.nuevo_siguiendo(nuevo_id, res_sig);
							if (res_sig != OK) {
								cout << "Error al añadir siguiendo: " << antiguo_id << " del usuario " << ptr->usuario.obtener_id() << endl;
							}
						}
					}
					if (ptr->usuario.me_sigue(antiguo_id)) {
						ptr->usuario.eliminar_seguidor(antiguo_id, res_seg);
						if (res_seg != OK) {
							cout << "Error al eliminar seguidor: " << antiguo_id << " del usuario " << ptr->usuario.obtener_id() << endl;
						}
						else {
							ptr->usuario.nuevo_seguidor(nuevo_id, res_seg);
							if (res_seg != OK) {
								cout << "Error al añadir seguidor: " << antiguo_id << " del usuario " << ptr->usuario.obtener_id() << endl;
							}
						}
					}
				}
				ptr = ptr->sig;
			}
			usuarios->usuario.establecer_id(nuevo_id);
		}
	}

	// Inserta un usuario en la lista de usuarios a los que sigue-
	// El usuario debe estar conectado y el usuario al que se quiere
	// seguir debe existir. Si no hay usuario conectado actualmente,
	// se devuelve 'false' a través de 'conectado'. Si el usuario que
	// se quiere incluir en la lista de usuarios seguidos no existe en la
	// red, se devuelve 'NO_EXISTE' a través de 'res'.
	// Si ambos usuarios existen, se actualizan las listas de seguidores
	// y siguiendo. Si la lista de seguidores o siguiendo están
	// llenas, se devuelve 'LISTA_LLENA' a través de 'res'.
	void Twitter::nuevo_siguiendo(const std::string &nuevo, Resultado &res, bool &conectado) {
		// caso 1.- No hay un usuario conectado
		if (usuario_conectado == nullptr) {
			conectado = false;
		}
		// caso 2.- Existe un usuario conectado
		else {
			conectado = true;
			// caso 2.1 - El usuaio conectado existe pero el usuario dado no se encuentra en la red
			PtrUsuario ptr = buscar_usuario(nuevo);
			if (ptr == nullptr) {
				res = NO_EXISTE;
			}
			// caso 2.2.- Existe ambos usuarios
			else {
				// Al añadir al usuario conectado el que le sigue, se añade al usuario seguido el usuario conectado como seguidor
				usuario_conectado->usuario.nuevo_siguiendo(nuevo, res);
				if (res == OK) {
					ptr->usuario.nuevo_seguidor(usuario_actual(),res);
					if (res == LISTA_LLENA) {
						usuario_conectado->usuario.eliminar_siguiendo(nuevo, res); // si estaba la lista llena se deshace el paso anterior para que todo cuadre
						res = LISTA_LLENA;
					}
				}
			}
		}
	}

	// Inserta un nuevo tweet al final de la lista de tweets. Si la lista de
	// tweets está llena, se devuelve 'LISTA_LLENA' a través de 'res'. Si no,
	// se devuelve 'OK'. La longitud máxima
	void Twitter::nuevo_tweet(const Tweet &nuevo, Resultado &res, bool &conectado) {
		// caso 1.- No hay un usuario conectado
		if (usuario_conectado == nullptr) {
			conectado = false;
		}
		// caso 2.- Existe un usuario conectado
		else {
			conectado = true;
			usuario_conectado->usuario.nuevo_tweet(nuevo, res);
		}
	}

	// Elimina un usuario en la lista de usuarios a los que sigue el usuario.
	// El usuario debe estar conectado y el usuario al que se quiere
	// dejar de seguir debe existir. Si no hay usuario conectado actualmente,
	// se devuelve 'false' a través de 'conectado'. Si el usuario que
	// se quiere eliminar de la lista de usuarios seguidos no existe en la
	// red, se devuelve 'NO_EXISTE' a través de 'res'. Si ambos usuarios
	// existen, se actualizan las lista se de seguidores y siguiendo,
	// eliminando los nombres de los usuarios correspondientes.
	void Twitter::eliminar_siguiendo(const std::string &usuario, Resultado &res, bool &conectado) {
		// caso 1.- No hay un usuario conectado
		if (usuario_conectado == nullptr) {
			conectado = false;
		}
		// caso 2.- Existe un usuario conectado
		else {
			conectado = true;
			// caso 2.1 - El usuaio conectado existe pero el usuario dado no se encuentra en la red
			PtrUsuario ptr = buscar_usuario(usuario);
			if (ptr == nullptr) {
				res = NO_EXISTE;
			}
			// caso 2.2.- Existe ambos usuarios
			else {
				// Al eliminar al usuario conectado el que le sigue, se elimina al usuario seguido el usuario conectado como seguidor
				usuario_conectado->usuario.eliminar_siguiendo(usuario, res);
				if (res == OK) {
					ptr->usuario.eliminar_seguidor(usuario_actual(), res);
					if (res == NO_EXISTE) {
						usuario_conectado->usuario.nuevo_siguiendo(usuario, res); // si estaba la lista llena se deshace el paso anterior para que todo cuadre
						res = NO_EXISTE;
					}
				}
			}
		}
	}

	// Se obtiene la lista de menciones que los demás usuarios de
	// la red tienen con el usuario actualmente conectado y se
	// almacenan en la lista de menciones del usuario actualmente
	// conectado.
	// Las menciones comienzan todas con el carácter ampsersand ('@').
	void Twitter::obtener_menciones(bool &conectado) {
		// caso 1.- No hay un usuario conectado
		if (usuario_conectado == nullptr) {
			conectado = false;
		}
		// caso 2.- Existe un usuario conectado
		else {
			conectado = true;
			Menciones mens;
			PtrUsuario ptr = usuarios;
			Resultado res_men = OK;
			// Usuario actual inicializa menciones
			usuario_conectado->usuario.eliminar_menciones();
			// Obtener menciones de todos los usuarios de la red con respecto al usuario conectado
			while (ptr != nullptr && res_men == OK) {
				ptr->usuario.obtener_menciones(usuario_actual(), mens);
				for (unsigned i = 0; i < mens.num_menciones; i++) {
					if (res_men == OK) { // Siempre que se pueda añadir mas menciones, se seguirá añadiendo
						usuario_conectado->usuario.nueva_mencion(mens.listado[i], res_men);
					}
				}
				ptr = ptr->sig; // Siguiente usuario
			}
		}
	}

	//------------------------------------------------------------------

	//------------------------------------------------------------------
	// MÉTODOS DE LA RED SOCIAL

	// Imprime por pantalla los usuarios actuales de la red social
	void Twitter::imprimir_usuarios() const {
		PtrUsuario ptr = usuarios;
		unsigned n = 0;
		cout << "------------ Lista de usuarios actuales en la red -----------------" << endl;
		while (ptr != nullptr) {
			n++;
			cout << "Nº: " << n << ": --------- " << ptr->usuario.obtener_id() << endl;
			ptr = ptr->sig;
		}
		cout << "------------------------------------------------- Total: " << n << endl;
	}

	// Cambia el usuario actualmente conectado a la red. Si el usuario
	// existe, se cambia el usuario y se devuelve 'OK' a través del
	// parámetro 'res'. Si el usuario no existe, se mantiene el usuario
	// actual y se devuelve 'NO_EXISTE' a través del parámetro 'res'
	void Twitter::cambiar_usuario_actual(const std::string &nuevo_id_actual, Resultado &res) {
		PtrUsuario ant = buscar_usuario(usuario_actual());
		PtrUsuario ptr = buscar_usuario(nuevo_id_actual);
		// caso 1.- No existe el usuario en la red
		if (ptr == nullptr) {
			res = NO_EXISTE;
		}
		// caso 2.- Existe el usuario en la red
		else {
			// Al cambiar de usuario se desea que se quede los cambios en la red
			ant->usuario = usuario_conectado->usuario;
			usuario_conectado = new NodoUsuario;
			usuario_conectado->usuario = ptr->usuario;
			usuario_conectado->sig = nullptr;
			res = OK;
		}
	}

	// Insertar un nuevo usuario en la red social, a partir de su
	// id de usuario, con todos sus datos vacíos (lista de seguidores,
	// lista de tweets, etc.). Si el id del nuevo usuario no existe,
	// se inserta en la red y se devuelve 'OK' a través del parámetro
	// 'res'. Si el usuario ya existía, se devuelve 'YA_EXISTE' a
	// través de 'res'.
	void Twitter::insertar_usuario(const std::string &nuevo_usuario, Resultado &res) {
		PtrUsuario ptr = buscar_usuario(nuevo_usuario);
		// caso 1.- No existe el usuario en la red
		if (ptr == nullptr) {
			insertar_usuario(UsuarioTwitter(nuevo_usuario));
			res = OK;
		}
		// caso 2.- Existe el usuario en la red
		else {
			res = YA_EXISTE;
		}
	}

	// Insertar un nuevo usuario en la red social.
	// Si el id del nuevo usuario no existe,
	// se inserta en la red y se devuelve 'OK' a través del parámetro
	// 'res'. Si el usuario ya existía, se devuelve 'YA_EXISTE' a
	// través de 'res'.
	void Twitter::insertar_usuario(const UsuarioTwitter &nuevo_usuario, Resultado &res) {
		PtrUsuario ptr = buscar_usuario(nuevo_usuario.obtener_id());
		// caso 1.- No existe el usuario en la red
		if (ptr == nullptr) {
			insertar_usuario(UsuarioTwitter(nuevo_usuario));
			res = OK;
		}
		// caso 2.- Existe el usuario en la red
		else {
			res = YA_EXISTE;
		}
	}

	// Elimina un usuario en la red social, a partir de su
	// id de usuario. Si el id del nuevo usuario existe,
	// se elimina de la red y se devuelve 'OK' a través del parámetro
	// 'res'. Deben actualizarse la lista de seguidores y siguiendo
	// en las listas de los demás usuarios de la red.
	// Si el usuario no existía, se devuelve 'NO_EXISTE' a
	// través de 'res'.
	void Twitter::eliminar_usuario(const std::string &usuario, Resultado &res) {
		PtrUsuario ptr = buscar_usuario(usuario);
		Usuarios lista;
		Menciones mens;
		string actual = usuario_actual();
		// caso 1.- No existe el usuario en la red
		if (ptr == nullptr) {
			res = NO_EXISTE;
		}
		// caso 2.- Existe el usuario en la red
		else {
			ptr = usuarios;
			while (ptr != nullptr) {
				// Borrar al usuario de la lista de siguiendo
				if (ptr->usuario.estoy_siguiendo(usuario)) {
					ptr->usuario.eliminar_siguiendo(usuario, res);
					if (res != OK) {
						cout << "Error al eliminar siguiendo: " << usuario << " del usuario " << ptr->usuario.obtener_id() << endl;
					}
				}
				// Borrar al usuario de la lista de seguidores
				if (ptr->usuario.me_sigue(usuario)) {
					ptr->usuario.eliminar_seguidor(usuario, res);
					if (res != OK) {
						cout << "Error al eliminar seguidor: " << usuario << " del usuario " << ptr->usuario.obtener_id() << endl;
					}
				}
				// Borrar menciones que el usuario a realizado con respecto a otro usuarios de la red
				ptr->usuario.obtener_lista_usuarios_que_te_han_mencionado(lista); // Se obtiene la lista de menciones que ha realizado el usuario ptr
				for (unsigned i = 0; i < lista.num_usuarios; i++) {
					ptr->usuario.obtener_menciones(mens); // Se obtiene mlas menciones de ptr
					ptr->usuario.eliminar_menciones(); // se elimina las menciones del usuario ptr
					for (unsigned j = 0; j < mens.num_menciones; j++) {
						if (mens.listado[j].id_usuario != usuario) { // Se reestablece las menciones (sin las que mencione al usuario a eliminar
							ptr->usuario.nueva_mencion(mens.listado[j], res);
						}
					}
				} // for
				ptr = ptr->sig;
			}	// while
			if (actual == usuario) {
				// El usuario actual es el usuario a eliminar
				delete usuario_conectado;
				usuario_conectado = nullptr;
			}
			else {
				// En caso contrario simplemente actualizar el usuario conectado
				delete usuario_conectado;
				usuario_conectado = new NodoUsuario;
				usuario_conectado->usuario = buscar_usuario(actual)->usuario;
			}
			borrar_usuario(usuario);
		} // else
	}

	// Recibe como parámetro el nombre del fichero con la lista de usuarios
	// de la red. A partir de ahí, carga desde disco todos los seguidores,
	// usuarios seguidos, tweets e menciones de cada uno de los
	// usuarios de la red.
	// Si el fichero de la lista de usuario existe, se procede a la carga
	// de la red desde disco y se devuelve 'true' a través del parámetro
	// 'red_cargada'. Si no, la red permanece vacía y se devuelve
	// 'false' a través del parámetro.
	// Los ficheros de datos de cada usuario tienen como nombre el
	// nombre del usuario y como extensión '.seg' para los seguidores,
	// '.sig' para los usuarios seguidos, '.twt' para los tweets
	// y (opcional) '.men' para las menciones (véase la clase UsuarioTwitter).
	void Twitter::cargar_red(const string &fic_lista_usuarios, bool &red_cargada) {
		// Variables
		ifstream fichero;
		string cadena;
		Resultado res_seg = OK, res_sig = OK, res_twt = OK, res_men = OK;
		PtrUsuario ptr;
		// Abrir fichero
		fichero.open((fic_lista_usuarios + ".usr").c_str());
		// Si no falla, leer los usuarios
		borrar_todo();
		if (!fichero.fail()) {
			getline(fichero, cadena);
			if (!fichero.fail()) {
				ptr = new NodoUsuario;
				ptr->usuario.establecer_id(cadena);
				ptr->usuario.cargar_todo(cadena, cadena, cadena, cadena, res_seg, res_sig, res_twt, res_men);
				usuarios = ptr;
				getline(fichero, cadena);
			}
			while (!fichero.fail() && cadena != "") {
				//UsuarioTwitter nuevo(cadena);
				ptr->sig = new NodoUsuario;
				ptr->sig->usuario.establecer_id(cadena);
				ptr->sig->usuario.cargar_todo(cadena, cadena, cadena, cadena, res_seg, res_sig, res_twt, res_men);
				ptr = ptr->sig;
				//insertar_usuario(cadena);
				getline(fichero, cadena);
			}
			ptr->sig = nullptr;
		}
		(res_seg == OK && res_sig == OK && res_twt == OK && res_men == OK)? red_cargada = true : red_cargada = false;
		fichero.close();
	}


	// Guarda toda la red social en disco. El nombre de fichero con los nombres de
	// usuario se pasa como parámetro. Los datos de cada usuario se guardan
	// según se indica en la clase UsuarioTwitter
	// Los ficheros de datos de cada usuario tienen como nombre el
	// nombre del usuario y como extensión '.seg' para los seguidores,
	// '.sig' para los usuarios seguidos, '.twt' para los tweets
	// y (opcional) '.men' para las menciones (véase la clase UsuarioTwitter).
	void Twitter::guardar_todo(const std::string &nom_fic_usuario) const {
		// Variables
		ofstream ficherousr;
		string cadena;
		Resultado res_seg = OK, res_sig = OK, res_twt = OK, res_men = OK;
		PtrUsuario ptr = usuarios;
		// Abrir fichero
		ficherousr.open((nom_fic_usuario + ".usr").c_str());
		// Si no falla, guardar los usuarios
		if (!ficherousr.fail() && ptr != nullptr) {
			cadena = ptr->usuario.obtener_id();
			ficherousr << cadena << endl;
			while (!ficherousr.fail() && ptr != nullptr) {
				ptr->usuario.guardar_todo(cadena, cadena, cadena, cadena, res_seg, res_sig, res_twt, res_men);
				ptr = ptr->sig;
				if (ptr != nullptr) {
					cadena = ptr->usuario.obtener_id();
					ficherousr << cadena << endl;
				}
			}
		}
		// Cerramos
		ficherousr.close();
	}
	//------------------------------------------------------------------
	//------------------------------------------------------------------
	// TIPOS PRIVADOS:
	//struct NodoUsuario {
	//	UsuarioTwitter usuario;
	//	NodoUsuario *sig;
	//};
	//typedef NodoUsuario *PtrUsuario;
	//------------------------------------------------------------------

	//------------------------------------------------------------------
	// ATRIBUTOS:
	//PtrUsuario usuarios; // Lista de todos los usuarios de la red
	//PtrUsuario usuario_conectado;  // Usuario actualmente conectado
									 // a la red social.
	//------------------------------------------------------------------

	//------------------------------------------------------------------
	// MÉTODOS PRIVADOS:

	// Busca un usuario en la lista de usuarios. Si lo encuentra,
	// devuelve un puntero al nodo de la lista que contiene el usuario.
	// Si no lo encuentra, devuelve nullptr
	Twitter::PtrUsuario Twitter::buscar_usuario(const std::string &id_usuario) const {
		// Puntero que apunta a la lista de usuarios
		PtrUsuario ptr = usuarios;
		// Mientras no encontremos ni el final, ni el usuario, seguimos recorriendo nodos
		while (ptr != nullptr && ptr->usuario.obtener_id() != id_usuario) {
			ptr = ptr->sig;
		}
		// Una vez encontrado el nodo, devolvemos ptr
		return ptr;
	}

	// Eliminar toda la lista de usuarios
	void Twitter::borrar_todo() {
		// Puntero que apunta a la lista de usuarios
		PtrUsuario ptr = usuarios;
		while (usuarios != nullptr) {
			usuarios = usuarios->sig;
			delete ptr;
			ptr = usuarios;
		}
	}

	// Insertar un nuevo usuario al final de la lista de usuarios
	void Twitter::insertar_usuario(const UsuarioTwitter &nuevo_usuario) {
		// Puntero al nuevo nodo
		PtrUsuario nuevonodo = new NodoUsuario;
		nuevonodo->usuario = nuevo_usuario;
		nuevonodo->sig = nullptr;
		// Caso 1.- Si la lista está vacía
		if (usuarios == nullptr) {
			usuarios = nuevonodo;
		}
		// Caso 2.- Si la lista no está vacía
		else {
			PtrUsuario ptr = usuarios;
			while (ptr->sig != nullptr) {
				ptr = ptr->sig;
			}
			ptr->sig = nuevonodo;
		}
	}

	// Eliminar un usuario de la lista de usuarios
	// PRECONDICIÓN: el usuario existe
	void Twitter::borrar_usuario(const std::string &id_usuario) {
		// Primero buscamos la posición del usuario y comprobamos que la precondición se cumpla
		PtrUsuario ptr = buscar_usuario(id_usuario);
		assert(ptr != nullptr);
		// Dado que ya tenemos el puntero al nodo del usuario a eliminar lo eliminamos
		// Caso 1.- El nodo es el primero
		if (ptr->usuario.obtener_id() == usuarios->usuario.obtener_id()) {
			borrar_todo();
		}
		// Caso 2.- El nodo existe y no es el primero
		else {
			PtrUsuario ant = usuarios;
			while (ant->sig->usuario.obtener_id() != ptr->usuario.obtener_id()) {
				ant = ant->sig;
			}
			// ptr apunta al nodo a eliminar, y ant apunta al nodo anterior
			ant->sig = ptr->sig;
			delete ptr;
		}
	}
}
