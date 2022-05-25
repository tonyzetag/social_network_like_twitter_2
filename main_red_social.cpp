#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "twitter.hpp"
#include "usuario_twitter.hpp"

#ifdef __LINUX__
void limpiar_pantalla() {
	system("clear");
}
#else
void limpiar_pantalla() {
	system("cls");
}
#endif // !

using namespace std;
using namespace bblProgII;

// Escribe el menú de opciones, lee la opción por teclado y la devuelve
char menu();

// Pulsar una tecla para continuar
void Seguir();

// Escribir resultado de operación por pantalla
void escribir_resultado(const Resultado res);

// Escribir resultado de conexión del usuario actual
void escribir_conectado(bool conectado);

int main() {
	/* ALUMNO:
    Declaraciones de datos: variables, objetos, etc.
	*/
	Twitter red;
	char opcion;
	bool conectado;
	Resultado res;
	string id_usuario, input;
	unsigned num_seg, num_sig, num_men, num_twt;
	Tweet nuevo_tweet;

	time_t tSac; // instante actual
	tm tms;

	limpiar_pantalla(); //// En Windows: system("cls");
	bool respuesta;

	/* ALUMNO: cargar toda la red social desde disco y obtener 'respuesta'*/
	red.cargar_red("mi_twitter", respuesta);
	if (respuesta) {
	cout << "LA RED SE HA CARGADO DE DISCO CORRECTAMENTE..." << endl;
	} else {
	cout << "NO SE HA PODIDO CARGAR LA RED DESDE DISCO..." << endl;
	}
	Seguir();

	do {
	opcion = menu();
	switch (opcion) {
	case 'a': /* Obtener id del usuario actualmente conectado */
		cout << "El usuario actual es: " << red.usuario_actual() << endl;
		Seguir();
		break;
	case 'b': /* Consultar si un usuario me sigue */
		cout << "Introduzca el nombre del usuario a comprobar si sigue al usuario actual: " << endl;
		getline(cin, id_usuario);
		red.me_sigue(id_usuario, respuesta, conectado);
		escribir_conectado(conectado);
		if (conectado) {
			(respuesta) ? cout << "El usuario " << id_usuario << " sigue al usuario actual" << endl : cout << "El usuario " << id_usuario << " no sigue al usuario actual";
		}
		Seguir();
		break;
	case 'c': /* Consultar si estoy siguiendo a un usuario */
		cout << "Introduzca el nombre del usuario a comprobar si el usuario actual sigue: " << endl;
		getline(cin, id_usuario);
		red.estoy_siguiendo(id_usuario, respuesta, conectado);
		escribir_conectado(conectado);
		if (conectado) {
			(respuesta) ? cout << "El usuario " << id_usuario << " está siguiendo al usuario actual" << endl : cout << "El usuario " << id_usuario << " no está siguiendo al usuario actual";
		}
		Seguir();
		break;
	case 'd': /* Imprimir mis estadísticas (seguidores, siguiendo, etc.) */
		red.num_seguidores(num_seg, conectado);
		red.num_siguiendo(num_sig, conectado);
		red.num_tweets(num_twt, conectado);
		red.num_menciones(num_men, conectado);
		escribir_conectado(conectado);
		if (conectado) {
			cout << "Estadisticas del usuario: " << red.usuario_actual() << endl
				<< "---------------------------------------------" << endl
				<< "Numero de personas que sigue el usuario actual: " << num_seg << endl
				<< "Numero de personas que siguen al usuario actual: " << num_sig << endl
				<< "Numero de tweets del usuario actual: " << num_twt << endl
				<< "Numero de menciones al usuario actual: " << num_men << endl
				<< "---------------------------------------------" << endl;
		}
		Seguir();
		break;
	case 'e': /* Imprimir mi lista de seguidores y usuarios a los que sigo */
		cout << "Introduzca el número de usuarios que el usuario actual sigue a mostrar (0 = todos): ";
		getline(cin, input);
		num_seg = atoi(input.c_str());
		cout << "Introduzca el número de usuarios que siguen al usuario actual a mostrar (0 = todos): ";
		getline(cin, input);
		num_sig = atoi(input.c_str());
		cout << "Seguidores: " << endl;
		red.imprimir_seguidores(num_seg, conectado);
		cout << "Siguiendos: " << endl;
		red.imprimir_siguiendo(num_sig, conectado);
		escribir_conectado(conectado);
		Seguir();
		break;
	case 'f': /* Imprimir mi lista de tweets */
		cout << "Introduzca el número de tweets a mostrar (0 = todos): ";
		getline(cin, input);
		num_twt = atoi(input.c_str());
		red.imprimir_tweets(num_twt, conectado);
		escribir_conectado(conectado);
		Seguir();
		break;
	case 'g': /* Imprimir mi lista de menciones por otros usuarios */
		cout << "Introduzca el número de menciones a mostrar (0 = todos): ";
		getline(cin, input);
		num_men = atoi(input.c_str());
		red.imprimir_menciones(num_men, conectado);
		escribir_conectado(conectado);
		Seguir();
		break;
	case 'h': /* Actualizar mi lista de menciones que me han hecho otros usuarios */
		red.obtener_menciones(conectado);
		escribir_conectado(conectado);
		if (conectado) {
			cout << "Se ha actualizado la lista de menciones al usuario actual" << endl;
		}
		Seguir();
		break;
	case 'i': /* Modificar el id de mi usuario */
		cout << "Introduzca el nuevo nombre de usuario para " << red.usuario_actual() << ": ";
		getline(cin, id_usuario);
		red.establecer_id(id_usuario, conectado);
		escribir_conectado(conectado);
		if (conectado) {
			cout << "Se ha actualizado el nombre de usuario satisfactoriamente" << endl;
		}
		Seguir();
		break;
	case 'j': /* Insertar un nuevo tweet */
		tSac = time(NULL); // instante actual
		tms = *localtime(&tSac);
		cout << "tweet (140 caracteres): ";
		getline(cin, input);
		nuevo_tweet.tweet = input;
		nuevo_tweet.fecha_hora.anyo = unsigned(tms.tm_year + 1900);
		nuevo_tweet.fecha_hora.dia = unsigned(tms.tm_mday);
		nuevo_tweet.fecha_hora.hora = unsigned(tms.tm_hour);
		nuevo_tweet.fecha_hora.mes = unsigned(tms.tm_mon + 1);
		nuevo_tweet.fecha_hora.minuto = unsigned(tms.tm_min);
		nuevo_tweet.fecha_hora.segundo = unsigned(tms.tm_sec);
		red.nuevo_tweet(nuevo_tweet, res, conectado);
		Seguir();
		break;
	case 'k': /* Insertar un nuevo usuario en mi lista de usuarios a los que sigo */
		cout << "Inserta el nombre el nuevo usuario que se desea seguir: ";
		getline(cin, id_usuario);
		red.nuevo_siguiendo(id_usuario, res, conectado);
		escribir_conectado(conectado);
		if (conectado) {
			escribir_resultado(res);
		}
		Seguir();
		break;
	case 'l': /* Eliminar un usuario de mi lista de usuarios a los que sigo */
		cout << "Inserta el nombre el usuario que se desea elimininar (de la lista que sigues): ";
		getline(cin, id_usuario);
		red.eliminar_siguiendo(id_usuario, res, conectado);
		escribir_conectado(conectado);
		if (conectado) {
			escribir_resultado(res);
		}
		Seguir();
		break;
	case 'm': /* Cambiar el usuario actualmente conectado */
		cout << "¿A que usuario deseas conectar?: ";
		getline(cin, id_usuario);
		red.cambiar_usuario_actual(id_usuario, res);
		escribir_resultado(res);
		Seguir();
		break;
	case 'n': /* Insertar un nuevo usuario en red */
		cout << "Inserta el nombre el nuevo usuario que se desea añadir a la red: ";
		getline(cin, id_usuario);
		red.insertar_usuario(id_usuario, res);
		escribir_resultado(res);
		Seguir();
		break;
	case 'o': /* Eliminar un usuario de la red */
		cout << "Inserta el nombre el usuario que se desea elimininar de la red social: ";
		getline(cin, id_usuario);
		red.eliminar_usuario(id_usuario, res);
		escribir_resultado(res);
		Seguir();
		break;
	case 'p': /* Imprimir la lista de usuarios de la red social */
		cout << "Lista de usuarios actuales en la red social" << endl;
		red.imprimir_usuarios();
		Seguir();
		break;
	case 'q': /* Guardar en disco la configuración actual de red social */
		cout << "Introduzca nombre para el fichero (.usr) con los datos del usuario: ";
		getline(cin, input);
		input = input.substr(0, input.find_last_of("."));
		cout << "Guardando toda la configuración..." << endl;
		red.guardar_todo(input);
		Seguir();
		break;
	case 'x': /* SALIR DEL PROGRAMA */
		Seguir();
		break;
	}
	} while (opcion != 'x');
}

char menu() {
	char opcion;

	limpiar_pantalla();

	do {
	cout << "MENÚ DE OPCIONES (elija una opción y pulse <enter>):" << endl << endl;
	cout << "a -> Obtener id del usuario actualmente conectado" << endl;
	cout << "b -> Consultar si un usuario me sigue" << endl;
	cout << "c -> Consultar si estoy siguiendo a un usuario" << endl;
	cout << "d -> Imprimir mis estadísticas (seguidores, siguiendo, etc.)" << endl;
	cout << "e -> Imprimir mi lista de seguidores y usuarios a los que sigo" << endl;
	cout << "f -> Imprimir mi lista de tweets" << endl;
	cout << "g -> Imprimir mi lista de menciones por otros usuarios" << endl;
	cout << "h -> Actualizar mi lista de menciones que me han hecho otros usuarios" << endl;
	cout << "i -> Modificar el id de mi usuario" << endl;
	cout << "j -> Insertar un nuevo tweet" << endl;
	cout << "k -> Insertar un nuevo usuario en mi lista de usuarios a los que sigo" << endl;
	cout << "l -> Eliminar un usuario de mi lista de usuarios a los que sigo" << endl;
	cout << "m -> Cambiar el usuario actualmente conectado" << endl;
	cout << "n -> Insertar un nuevo usuario en red" << endl;
	cout << "o -> Eliminar un usuario de la red" << endl;
	cout << "p -> Imprimir la lista de usuarios de la red social" << endl;
	cout << "q -> Guardar en disco la configuración actual de red social" << endl;
	cout << "x -> SALIR DEL PROGRAMA" << endl;

	cin.get(opcion); cin.ignore(); opcion = char(tolower(int(opcion)));
	} while ((opcion < 'a' || opcion > 'q') && (opcion != 'x'));

	return opcion;
}

void Seguir() {
	string enter;
	cout << endl << "Pulse <enter> para continuar..." << endl;
	getline(cin, enter);
}


void escribir_resultado(const Resultado res) {
	switch (res) {
	case OK: cout << "Operación realizada correctamente." << std::endl;
	break;
	case LISTA_LLENA: cout << "Operación NO realizada: lista llena." << std::endl;
	break;
	case YA_EXISTE: cout << "Operación NO realizada: el elemento ya existe" << std::endl;
	break;
	case NO_EXISTE: cout << "Operación NO realizada: el elemento no existe" << std::endl;
	break;
	case FIC_ERROR: cout << "Error en la apertura de fichero" << std::endl;
	}
}

void escribir_conectado(bool conectado) {
	if ((conectado) == true) {
		// Operación correcta, no hace falta informar
	} else {
		cout << "No existe un usuario conectado actualmente." << std::endl;
	}
}
