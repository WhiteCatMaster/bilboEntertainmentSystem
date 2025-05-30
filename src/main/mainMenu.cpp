#include "../gui/suicidios/main.h"
#include <iostream>
#include <limits>
using namespace std;

int main()
{
    string input;
    char eleccion;
    string password;

    while (true)
    {
        
        cout << R"(
    Elige que actividad en BES deseas hacer
    1) Cine 
    2) Libreria
    3) Cabina de suicidios
    4) GestionAdministrador
    5) Salir
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
            cout << "Cine seleccionado\n";
            break;

        case '2':
            cout << "Libreria seleccionada\n";
            break;

        case '3':
            mainSuicidios();
            break;

        case '4':
            cout << "Escriba la contraseña: ";
            cin >> password;
            if (password == "root")
            {
                cout << "Acceso concedido al modo administrador\n";
                // codigo admin
            }
            else
            {
                cout << "Contraseña incorrecta\n";
            }
            break;

        case '5':
            cout << "Saliendo...\n";
            return 0;
        }
    }

    return 0;
}
