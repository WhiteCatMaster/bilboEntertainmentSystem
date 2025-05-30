#include "../gui/suicidios/main.h"
#include "../gui/libreria/libreriaMain/mainlibreria.h"
#include "../gui/cine/cineMain/main.h"
#include <iostream>
#include <limits>
#include "../../src/gui/sockets/client.h"
#include "Admin.h"
using namespace std;

int main()
{
    
    string input;
    char eleccion;
    string password;

    while (true)
    {    
        cout << R"(
Elige que actividad de BES deseas hacer
1) Cabina de suicidios
2) GestionAdministrador
3) Salir
Eleccion: )";

    getline(cin, input); 

    if (input.size() != 1 || input[0] < '1' || input[0] > '5') {
        cout << R"(
    Numero no valido!
        )";
        continue;
    }

    eleccion = input[0];

    switch (eleccion)
    {
        case '1':
            mainSuicidios();
            break;

        case '2':
            cout << "Escriba la contraseña: ";
            cin >> password;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (password == "root")
            {
                cout << "\n";
                cout << "Acceso concedido al modo administrador\n";
                cout << "\n";
                mainadmin();
            }
            else
            {
                cout << "\n";
                cout << "Contraseña incorrecta\n";
            }
            break;

        case '3':
            cout << "\n";
            cout << "Saliendo del programa...\n";
            return 0;
        }
    }

    return 0;
}
