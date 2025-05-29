#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../BBDD/cineDB.h"
#include "libreria.h"
#include <time.h>
#define CINE_DB_H
#define MAX_LINE 1000

int mostrarLibrosDisponibles() {
    int opcion = -1;
    int resultado;

    printf("-----------------------------\n");
    printf("LIBROS DISPONIBLES:\n");

    Libro *libros;
    int cuantosLibros = count_libros();

    if (cuantosLibros == 0) {
        borrarbdLibro();
        leer_csv("src/gui/libreria/libreriaMain/LibrosBien.csv");
        cuantosLibros = count_libros();
    }

    libros = show_libro();
    if (libros == NULL || cuantosLibros <= 0) {
        printf("No hay libros disponibles.\n");
        return -1;
    }

    for (int i = 0; i < cuantosLibros; i++) {
        printf("%d. %s\n", i + 1, libros[i].nombre);
    }

    printf("-----------------------------\n");

    while (1) {
        printf("Selecciona un libro (1-%d): ", cuantosLibros);
        if (scanf("%d", &opcion) != 1) {
            printf("Entrada invalida. Intentalo de nuevo.\n");
            while (getchar() != '\n'); // Limpiar stdin
        } else if (opcion < 1 || opcion > cuantosLibros) {
            printf("Por favor, selecciona un libro valido...\n");
        } else {
            break;
        }
    }

    resultado = unLibro(libros, opcion - 1);

    free(libros);
    return resultado;
}


int unLibro(Libro *libros, int num) {
    char opcion2;
    int devolver = -1;

    printf("-----------------------------\n"); 
    printf("Ficha del libro:\n");
    printf("Nombre: %s\n", libros[num].nombre);
    printf("Genero: %s\n", libros[num].genero);
    printf("Descripcion: %s\n", libros[num].descripcion);
    printf("Precio compra: %f\n", libros[num].precioCo);
    printf("Precio alquilado: %f\n", libros[num].precioAl);
    printf("-----------------------------\n");
    printf("P [Pagar]\n");
    printf("V [Volver]\n");
    while (getchar() != '\n');
    scanf("%c", &opcion2);

    if(opcion2 == 'V') {
        devolver = -1;
    } else if(opcion2 == 'P') {
        devolver = num;
    }

    return devolver;
}

Libro pagarTarjetas(int numlibro, int numtarjetas) {
    while (getchar() != '\n');

    time_t t;
    struct tm *tm_info;
    time(&t);
    tm_info = localtime(&t);
    int dia = tm_info->tm_mday;
    int mes = tm_info->tm_mon + 1;
    int ano = tm_info->tm_year + 1900; 

    int proxdia;
    int proxmes;
    int proxano;

    Libro *libros;
    int cuantosLibros = 0;

    Tarjeta *tarjetas;

    libros = show_libro();
    tarjetas = show_tarjeta();

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
        printf("%d. Numero:%s CVV:%d Saldo:%f\n",i + 1, tarjetas[i].numero, tarjetas[i].CVV, tarjetas[i].saldo);
    }
    printf("-----------------------------\n");
    printf("Selecciona una tarjeta:\n");
    scanf("%d", &seleccion);
    seleccionado = seleccion;

    if(seleccion < 1 || seleccion > numtarjetas) {
        printf("Por favor, selecciona una tarjeta valida...\n");
    } else {
        while (getchar() != '\n');
        printf("-----------------------------\n");
        printf("Comprar [C] o Alquilar [A]?\n");
        scanf("%c", &seleccion2);

        if(seleccion2 == 'C') {
            if(tarjetas[seleccionado-1].saldo > libroSeleccionado.precioCo) {
                printf("Compra finalizada; el libro se ha anadido al inventario\n");
                delete_libro(libropuntero);
                float nuevoSaldo = tarjetas[seleccionado-1].saldo - libroSeleccionado.precioCo;
                update_saldo(tarjetas[seleccionado-1], nuevoSaldo);
                insert_inventario(&libroSeleccionado, 01, 0, 2999);
            } else {
                printf("No tienes suficiente saldo para comprar el libro.\n");
            }
        } else if(seleccion2 == 'A') {
            if(tarjetas[seleccionado-1].saldo > libroSeleccionado.precioAl) {
                printf("Compra finalizada; el libro se ha anadido al inventario\n");
                delete_libro(libropuntero);
                float nuevoSaldo = tarjetas[seleccionado-1].saldo - libroSeleccionado.precioAl;
                update_saldo(tarjetas[seleccionado-1], nuevoSaldo);

                if(dia < 19) {
                    proxdia = dia + 10;
                    proxmes = mes;
                    proxano = ano;
                } else {
                    proxdia = 30 - dia;
                    if (mes == 11) {
                        proxmes = 0;
                        proxano = ano + 1;
                    } else {
                        proxmes = mes + 1;
                        proxano = ano;
                    } 
                }

                insert_inventario(&libroSeleccionado, proxdia, proxmes, proxano);
            } else {
                printf("No tienes suficiente saldo para comprar el libro.\n");
            }
        }
    }
    free(tarjetas);
    free(libros);
    return libroSeleccionado;
}

void cargarTarjetas(Tarjeta **tarjetas, int cuantasTarjetas) {
    while (getchar() != '\n');

    for(int i=0;i<cuantasTarjetas;i++) {
        insert_tarjeta(*tarjetas[i]);
    }
}

void mostrarInventario() {
    time_t t;
    struct tm *tm_info;
    time(&t);
    tm_info = localtime(&t);
    int dia = tm_info->tm_mday;
    int mes = tm_info->tm_mon + 1;
    int ano = tm_info->tm_year + 1900;

    Tarjeta *tarjetas;
    tarjetas = show_tarjeta();

    char opcion;
    int opcion2;

    printf("-----------------------------\n");
    printf("Libros en el inventario:\n");

    int cuantos;
    cuantos = count_inventario();

    if(cuantos == 0) {
        printf("No hay libros en el inventario\n");
        printf("-----------------------------\n");
    } else {
        int cuantosinv;
        cuantosinv = count_inventario();
        Libro *librosinv;
        librosinv = show_inventario();

        for(int i=0;i<cuantosinv;i++) {
            if(getanoInventarioPorNombre(librosinv[i].nombre) == 2999) {
                printf("%d. %s (Comprado)\n",i+1, librosinv[i].nombre);
            } else {
                if(getdiaInventarioPorNombre(librosinv[i].nombre) == dia && getmesInventarioPorNombre(librosinv[i].nombre) == mes && getanoInventarioPorNombre(librosinv[i].nombre) == ano) {
                    delete_libroInventario(&librosinv[i]);
                    insert_libro(&librosinv[i]);
                    update_saldo(tarjetas[0], tarjetas[0].saldo - 100);
                } else {
                    printf("%d. %s (%d-%d-%d)\n",i+1, librosinv[i].nombre, getdiaInventarioPorNombre(librosinv[i].nombre), getmesInventarioPorNombre(librosinv[i].nombre), getanoInventarioPorNombre(librosinv[i].nombre));
                }
            }
        }
        printf("-----------------------------\n");
        printf("D [Devolver]\n");
        printf("V [Volver]\n");
        scanf(" %c", &opcion);
        if(opcion == 'D') {
            printf("Selecciona un libro que devolver:\n");
            scanf(" %d", &opcion2);
            if(getanoInventarioPorNombre(librosinv[opcion2-1].nombre) == 2999) {
                printf("Selecciona un libro alquilado!\n");
            } else {
                printf("Devolucion completada!\n");
                delete_libroInventario(&librosinv[opcion2-1]);
                insert_libro(&librosinv[opcion2-1]);
            }
        }

        free(librosinv);
    }
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

        insert_libro(&lib);
    }

    fclose(file);
}
