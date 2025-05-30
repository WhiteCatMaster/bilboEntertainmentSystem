#include "../gui/libreria/libreriaMain/mainlibreria.h"
#include "../gui/cine/cineMain/main.h"
#include "../BBDD/cineDB.h"
#include "../gui/sockets/server.h"
#include "mainMenu.h"

int opcionn;

int selector()
{
    printf("Elige que actividad de BES deseas hacer\n");
    printf("1) Cine\n");
    printf("2) Libreria\n");
    printf("3) Sockets\n");
    printf("4) Salir\n");

    printf("Decide: ");
    scanf(" %d", &opcionn);
    printf("\n");


    if(opcionn == 2) {
        printf("Entrando en la libreria...\n");
        printf("\n");
        mainlibreria();
    } else if (opcionn == 4) {
        printf("Saliendo del programa...\n");
        return 0;
    } else if (opcionn == 3) {
        printf("Has seleccionado los Sockets\n");
        serverMain(); 
        printf("Has seleccionado los Sockets\n");
    } 
    else if (opcionn == 1) {
        printf("Entrando en el cine...\n");
        printf("\n");
        mainCine();
    } else {
        printf("Opción no válida\n");
    }

    return 0;
}


int main()
{
    //int seleccion = 1; // aqui va cambiando el valor
    selector();
}
