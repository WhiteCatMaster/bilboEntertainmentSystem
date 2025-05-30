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