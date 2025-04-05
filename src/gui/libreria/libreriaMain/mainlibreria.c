#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../../BBDD/cineDB.h"
#include "libreria.h"

char opcion;

int main(int argc, char const *argv[]) {
    int numeroLibro;

    Tarjeta t1; t1.CVV = 123; strcpy(t1.numero, "1234 5678 9876 5432"); t1.saldo = 1000.50;
    Tarjeta t2; t2.CVV = 456; strcpy(t2.numero, "4321 8765 6789 1234"); t2.saldo = 0;
    Tarjeta t3; t3.CVV = 789; strcpy(t3.numero, "9876 5432 1234 5678"); t3.saldo = 1200.30;

    Tarjeta* tarjetas[] = {&t1, &t2, &t3};

    printf("BIENVENIDO A LA LIBRERIA!!\n");
    printf("-----------------------------\n");
    printf("I [Inventario]\n");
    printf("L [Libros]\n");
    printf("F [Vaciar BD]\n");

    scanf(" %c", &opcion);
        if(opcion == 'L') {
            numeroLibro = mostrarLibrosDisponibles();
        } else if (opcion == 'F') {
            borrarbdLibro();
        }
    
    pagarTarjetas(tarjetas, numeroLibro, 3);
    


}
