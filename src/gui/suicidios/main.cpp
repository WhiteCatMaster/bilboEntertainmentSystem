#include "main.h"


Usuario logIn()
{
    string nombre;
    int edad;
    cout<< R"(
    bienvenidos a la KillZone
    de BES, vamos a hacer todo lo posible
    para q se muera :(Y/n)
    	⊂(◉‿◉)つ
    )";
    string notUsableVar;
    cin >>  notUsableVar;
    cout<< R"(
    Ahora necesita escribir sus datos:
    Que tedioso no? pero no se corte las venas 
    que para eso estamos nosotros
        ԅ(≖‿≖ԅ)
    Nombre:)";
    cin >> nombre;
    cout<< R"(
    Hora escribe tu puntuación
    (años sobrevividos)
    	(_゜_゜_)
    Edad:)";
    cin >> edad;
    return Usuario(nombre, edad);

}

KillSesion menuSeleccionTipoMuerte(Usuario usuarioEscogido)
{
    char seleccion;
    cout<<"hola "<<usuarioEscogido.getNombre()<<" ahora debera escoger su tipo de muerte"<<R"(
    1-> quemado
    2-> ahogado
    3-> acuchillado
    4-> congelado
    5-> muerte por aburrimiento
    6-> paro cardiaco
    7-> derrame cerebral
    	¯\(°_o)/¯
    introduce numero : )";
    cin >> seleccion;
    switch (seleccion)
    {
        case '1':
            return KillSesion(usuarioEscogido,"quemado");
        case '2': 
            return KillSesion(usuarioEscogido, "ahogado");
        case '3':
            return KillSesion(usuarioEscogido, "cuchillado");
        case '4':
            return KillSesion(usuarioEscogido, "congelado");
        case '5':
            return KillSesion(usuarioEscogido, "aburrimiento");
        case '6':
            return  KillSesion(usuarioEscogido, "paro cardiaco");
        case '7':
            return KillSesion(usuarioEscogido, "derrame cerebral");


        
    }
    
    return KillSesion(usuarioEscogido, "otra muerte" );
}
void imprimirRecibo(KillSesion sesion, Usuario user)
{
    cout<<R"(
            RECIBO
            id : )" << user.getId()<< R"(
            nombre: )"<< user.getNombre() << R"(
            score: )"<< user.getEdad() << R"(
            motivo de muerte: )"<<sesion.getTipoMuerte() <<R"(
            a dia :)" <<sesion.getDia()<<"/"<<sesion.getMes()<<"/"<<sesion.getAnyo();
}

int mainSuicidios()
{
    Usuario usuario = logIn();
    KillSesion sesion = menuSeleccionTipoMuerte(usuario);
    imprimirRecibo(sesion, usuario);
    
    return 0;
}