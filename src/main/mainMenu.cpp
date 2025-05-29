#include "../gui/suicidios/main.h"

int main()
{
    char eleccion;
    string password;
    cout<< R"(
    Elige que actividad en BES deseas hacer
    1) Cine 
    2) Libreria
    3) Cabina de suicidios
    4) GestionAdministrador
    eleccion: )";
    cin>> eleccion;
    switch (eleccion)
    {
    case '1':
        // socket a C 
    case '2':
        // socket a C
    case '3':
        mainSuicidios();
    case '4': 
        cout<< "escribe la constraseña: ";
        cin >> password;
        if( password == "root")
        {
            // codigo admin 
        }
    
    case !(1,2,3,4):
        cout<<"opcion no disponible";
        main();
    }
    return 0;
}
