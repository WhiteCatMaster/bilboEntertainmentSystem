#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../BBDD/cineDB.h"
#include "libreria.h"
#define CINE_DB_H //PROBAR LUEGO A QUITAR

#define MAX_LINE 1000

int mostrarLibrosDisponibles() {
    int opcion;
    int resultado;

    printf("-----------------------------\n");
    printf("LIBROS DISPONIBLES:\n");
    Libro *libros;
    int cuantosLibros = 0;

    int comprobacion = 0;
    comprobacion = count_libros();

    if(comprobacion == 0) {
        printf("BD VACIA\n");
        borrarbdLibro();
        leer_csv("C:/Users/aitor.sagarduy/Downloads/LibrosBien.csv");
    } else {
        printf("BD LLENA");
    }

    libros = show_libro();
    cuantosLibros = count_libros();

    for(int i=0;i<cuantosLibros;i++) {
        printf("%d. %s\n", i+1, libros[i].nombre);
    }
    printf("-----------------------------\n");
    printf("Selecciona un libro:\n");

    scanf(" %d", &opcion);
    if(opcion>cuantosLibros) {
        printf("Por favor, selecciona un libro valido...\n");
        mostrarLibrosDisponibles();
    } else if(opcion < 0) {
        printf("Por favor, selecciona un libro valido...\n");
        mostrarLibrosDisponibles();
    } else {
        resultado = unLibro(libros, opcion-1);

    }

    return resultado;
}

int unLibro(Libro *libros, int num) {
    char opcion2;
    int devolver = 0;

    printf("-----------------------------\n"); 
    printf("Ficha del libro:\n");
    printf("Nombre: %s\n", libros[num].nombre);
    printf("Genero: %s\n", libros[num].genero);
    printf("Descripcion: %s\n", libros[num].descripcion);
    printf("Precio compra: %f\n", libros[num].precioCo);
    printf("Precio alquilado: %d\n", libros[num].precioAl);
    printf("-----------------------------\n");
    printf("P [Pagar]\n");
    printf("V [Volver]\n");
    while (getchar() != '\n');
    scanf("%c", &opcion2);

    if(opcion2 == 'V') {
        while (getchar() != '\n');
        mostrarLibrosDisponibles();
    } else if(opcion2 == 'P') {
        devolver = num;
    } else {
        unLibro(libros, num);
    }

    return devolver;
}

Libro pagarTarjetas(Tarjeta **tarjetas, int numlibro, int numtarjetas) {
    Libro *libros;
    int cuantosLibros = 0;

    libros = show_libro();

    Libro libroSeleccionado;
    Libro *libropuntero;
    libropuntero = &libroSeleccionado;

    libroSeleccionado = libros[numlibro];

    int seleccion;
    int seleccionado;
    char seleccion2;

    printf("-----------------------------\n"); 
    printf("Tarjetas disponibles:\n");
    for(int i = 0; i < numtarjetas; i++) {
        printf("%d. Numero:%s CVV:%d Saldo:%f\n",i + 1, tarjetas[i]->numero, tarjetas[i]->CVV, tarjetas[i]->saldo);
    }
    printf("-----------------------------\n");
    printf("Selecciona una tarjeta:\n");
    scanf("%d", &seleccion);
    seleccionado = seleccion;

    if(seleccion < 0) {
        printf("Por favor, selecciona una tarjeta valida...\n");
        pagarTarjetas(tarjetas ,numlibro, numtarjetas);
    } else if (seleccion > numtarjetas) {
        printf("Por favor, selecciona una tarjeta valida...\n");
        pagarTarjetas(tarjetas ,numlibro, numtarjetas);
    } else {
        while (getchar() != '\n');
        printf("-----------------------------\n");
        printf("Comprar [C] o Alquilar [A]?\n");
        scanf("%c", &seleccion2);

        if(seleccion2 == 'C') {
            if(tarjetas[seleccionado-1]->saldo > libroSeleccionado.precioCo) {
                printf("Compra finalizada; el libro se ha añadido al inventario\n");
                delete_libro(libropuntero);
            } else {
                printf("No tienes suficiente saldo para comprar el libro.\n");
            }
        } else if(seleccion2 == 'A') {
            if(tarjetas[seleccionado-1]->saldo > libroSeleccionado.precioAl) {
                printf("Compra finalizada; el libro se ha anadido al inventario\n");
                delete_libro(libropuntero);
            } else {
                printf("No tienes suficiente saldo para comprar el libro.\n");
            }

        } else {
            pagarTarjetas(tarjetas, numlibro, numtarjetas);
        }
    }

    return libroSeleccionado;
}


void leer_csv(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error al abrir el archivo");
        return;
    }

    char line[MAX_LINE];

    while (fgets(line, sizeof(line), file)) {
        char *nombre, *descripcion, *genero;
        float precioCo, precioAl;

        // Usar ";" como delimitador
        nombre = strtok(line, ";");
        descripcion = strtok(NULL, ";");
        precioCo = atof(strtok(NULL, ";"));
        precioAl = atof(strtok(NULL, ";"));
        genero = strtok(NULL, ";\n");
       
        Libro lib;
        lib.nombre =nombre;
        lib.descripcion= descripcion;
        lib.precioCo = precioCo;
        lib.precioAl = precioAl; 
        lib.genero= genero;

        insert_libro(&lib); // Insertar el libro en la base de datos

    }

    fclose(file);
}

