#include "mainlibreria.h"
#include "../../../BBDD/cineDB.h"
#include "../../../main/mainMenu.h"

char opcion;

int mainlibreria() {
    int tarjetasSiNo = 0;

    Tarjeta t1; t1.CVV = 123; strcpy(t1.numero, "1234 5678 9876 5432"); t1.saldo = 1000.50;
    Tarjeta t2; t2.CVV = 456; strcpy(t2.numero, "4321 8765 6789 1234"); t2.saldo = 0;
    Tarjeta t3; t3.CVV = 789; strcpy(t3.numero, "9876 5432 1234 5678"); t3.saldo = 1200.30;

    Tarjeta* tarjetas[] = {&t1, &t2, &t3};

    int cuantasTarjetas = count_tarjetas();
    if(cuantasTarjetas == 0) {
        cargarTarjetas(tarjetas, 3);
    }

    while (1) {
        int numeroLibro;
        tarjetasSiNo = 0;

        while (getchar() != '\n');
        printf("BIENVENIDO A LA LIBRERIA!\n");
        printf("-----------------------------\n");
        printf("I [Inventario]\n");
        printf("L [Libros]\n");
        printf("S [Salir]\n");

        scanf(" %c", &opcion);
        if(opcion == 'L') {
            numeroLibro = mostrarLibrosDisponibles();
            if (numeroLibro != -1) {
                pagarTarjetas(numeroLibro, 3);
            }
        } else if (opcion == 'I') {
            mostrarInventario();
        } else if (opcion == 'S') {
            printf("\n");
            printf("Saliendo de la libreria...\n");
            printf("\n");
            selector();
        } else {
            printf("-----------------------------\n");
            printf("Selecciona un caracter valido!\n");
            printf("\n");
        }
    }

    return 0;
}
