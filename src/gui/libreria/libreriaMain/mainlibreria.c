#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../../BBDD/cineDB.h"
#include "libreria.h"
#include <time.h>

char opcion;

int main(int argc, char const *argv[]) {
    int numeroLibro;
    int tarjetasSiNo = 0;

    //Crear 3 valores estaticos de tarjetas
    Tarjeta t1; t1.CVV = 123; strcpy(t1.numero, "1234 5678 9876 5432"); t1.saldo = 1000.50;
    Tarjeta t2; t2.CVV = 456; strcpy(t2.numero, "4321 8765 6789 1234"); t2.saldo = 0;
    Tarjeta t3; t3.CVV = 789; strcpy(t3.numero, "9876 5432 1234 5678"); t3.saldo = 1200.30;

    //Preparar array de punteros de las tarjetas
    Tarjeta* tarjetas[] = {&t1, &t2, &t3};

    //Si no hay ninguna tarjeta guardada en la BD, las carga
    int cuantasTarjetas = count_tarjetas();
    if(cuantasTarjetas == 0) {
        cargarTarjetas(tarjetas, 3);
    }

    printf("BIENVENIDO A LA LIBRERIA!!\n");
    printf("-----------------------------\n");
    printf("I [Inventario]\n");
    printf("L [Libros]\n");
    printf("F [Vaciar BD]\n");

    scanf(" %c", &opcion);
        //Se lleva a otra funcion encargada de mostrar los libros
        if(opcion == 'L') {
            //Se carga el numero (en la lista) del libro que se quiere comprar
            numeroLibro = mostrarLibrosDisponibles();
        //Para vaciar la BD entera y asi recargar los datos originales
        } else if (opcion == 'F') {
            borrarbdLibro();
            borrarbdTarjeta();
            borrarbdInventario();
            tarjetasSiNo = 1;
        //Lleva al inventario con los libros comprados/alquilados
        } else if (opcion == 'I') {
            mostrarInventario();
        } else {
        //Se reinicia el proceso de haber elegido un caracter no valido
            printf("-----------------------------\n");
            printf("Selecciona un caracter valido!\n");
            exit(0);
        }
    
    //Se lleva a la funcion de pagar el libro, llevando como parametros el numero del libro y la cantidad de tarjetas que hay
    if(tarjetasSiNo == 0) {
        pagarTarjetas(numeroLibro, 3);
    }
    


}
