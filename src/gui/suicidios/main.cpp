#include "main.h"


Usuario logIn()
{
    string nombre;
    int edad;
    string respuesta;
    string edadStr;

    do {
        cout << R"(
    Bienvenido a la KillZone de BES, vamos a hacer todo lo posible para que se muera:
    	⊂(◉‿◉)つ    
    Esta de acuerdo? (Y/n): )";
    cin >> respuesta;
    transform(respuesta.begin(), respuesta.end(), respuesta.begin(), ::tolower);
    } while (respuesta != "y" && respuesta != "n");

    if (respuesta == "n") {
    cout << R"(
    La salvacion nunca fue una opcion.
    )";
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << R"(
    Ahora necesita escribir sus datos:
    Que tedioso no? pero no se corte las venas 
    que para eso estamos nosotros
        ԅ(≖‿≖ԅ)
    Nombre: )";
    
    getline(cin, nombre);

    do {
        cout << R"(
    Ahora escriba su puntuación (años sobrevividos)
    	( •_•)
    Edad: )";
        cin >> edadStr;
    } while (!all_of(edadStr.begin(), edadStr.end(), ::isdigit));

    edad = stoi(edadStr);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return Usuario(nombre, edad);
}


KillSesion menuSeleccionTipoMuerte(Usuario usuarioEscogido)
{
    string seleccion;
    char tipo;

    do {
    cout << "Hola, " << usuarioEscogido.getNombre() << ". Ahora debera escoger el tipo de muerte que desea" << R"(
    1-> Quemado
    2-> Ahogado
    3-> Acuchillado
    4-> Congelado
    5-> Muerte por aburrimiento
    6-> Paro cardiaco
    7-> Derrame cerebral
    	¯\(°_o)/¯
    Introduzca el numero : )";

        getline(cin, seleccion);
    } while (seleccion.size() != 1 || seleccion[0] < '1' || seleccion[0] > '7');

    tipo = seleccion[0];

    switch (tipo)
    {
        case '1':
            return KillSesion(usuarioEscogido, "Quemado");
        case '2':
            return KillSesion(usuarioEscogido, "Ahogado");
        case '3':
            return KillSesion(usuarioEscogido, "Acuchillado");
        case '4':
            return KillSesion(usuarioEscogido, "Congelado");
        case '5':
            return KillSesion(usuarioEscogido, "Aburrimiento");
        case '6':
            return KillSesion(usuarioEscogido, "Paro cardiaco");
        case '7':
            return KillSesion(usuarioEscogido, "Derrame cerebral");
    }

    return KillSesion(usuarioEscogido, "Otra muerte");
}
void imprimirRecibo(KillSesion sesion, Usuario user)
{
    cout << "----------------------------------------------------";
    cout << R"(
    RECIBO:
    ID: )" << user.getId()<< R"(
    Nombre: )"<< user.getNombre() << R"(
    Puntuacion: )"<< user.getEdad() << R"(
    Causa de muerte: )"<<sesion.getTipoMuerte() <<R"(
    Dia de la defuncion: )" <<sesion.getDia()<<"/"<<sesion.getMes()<<"/"<<sesion.getAnyo() << "\n";
    cout << "----------------------------------------------------";
}

int mainSuicidios()
{
    Usuario usuario = logIn();
    KillSesion sesion = menuSeleccionTipoMuerte(usuario);
    imprimirRecibo(sesion, usuario);
    insert_muerte(&sesion, &usuario);
    
    return 0;
}