#include <iostream>
#include "../gui/sockets/client.h"
#include "Admin.h"
#include <limits>

using namespace std;

void mostrarMenu() {
    cout << "================================" << endl;
    cout << " Bienvenido al menu de admin     " << endl;
    cout << "================================" << endl;
    cout << "Seleccione una opcion:" << endl;
    cout << "1) Borrar base de datos de Libros" << endl;
    cout << "2) Borrar base de datos de Tarjetas" << endl;
    cout << "3) Borrar base de datos de Inventario" << endl;
    cout << "4) Borrar base de datos de Pelicula" << endl;
    cout << "5) Borrar base de datos de Critica" << endl;
    cout << "6) Borrar base de datos de Suicidios" << endl;
    cout << "7) Ver usuarios eliminados" << endl;
    cout << "--------------------------------" << endl;
    cout << "S) Salir" << endl;
    cout << "Ingrese su opcion: ";
}

int mainadmin() {
    string entrada;

    while (true) {
        mostrarMenu();
        getline(cin, entrada);

        if (entrada == "S" || entrada == "s") {
            cout << "Saliendo del programa...\n" << endl;
            return 0;
        }
        if(entrada == "6")
        {
            cout << "Borrando base de datos de suicidios..." << endl;
            if (borrardbMuerte() == 0) {
                cout << "Base de datos de suicidios borrada correctamente." << endl;
            } else {
                cout << "Error al borrar la base de datos de suicidios." << endl;
            }
            continue;
        }
        if (entrada == "7") {
            Usuario* usuarios = show_usuarios();
            if (usuarios != NULL) {
                cout << "Usuarios eliminados:" << endl;
                for (int i = 0; usuarios[i].getId() != 0; i++) {
                    cout << "ID: " << usuarios[i].getId() 
                         << ", Nombre: " << usuarios[i].getNombre() 
                         << ", Edad: " << usuarios[i].getEdad() << endl;
                }
                delete[] usuarios;
            } else {
                cout << "No se pudieron recuperar los usuarios eliminados." << endl;
            }
            continue;
        }
        try {
            int opcion = stoi(entrada);

            if (opcion >= 1 && opcion <= 5) {
                enviarMensaje('0' + opcion); 
                cout << "Solicitud enviada al servidor para borrar la opción" << opcion << "." << endl;
            } else {
                cout << "\nOpción no válida. Intente de nuevo.\n" << endl;
            }
        } catch (...) {
            cout << "\nEntrada no válida. Intente de nuevo.\n" << endl;
        }
    }
}