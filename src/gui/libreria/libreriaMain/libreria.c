#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../BBDD/cineDB.h"


#define MAX_LIBROS 10
#define MAX_TARJETAS 2

typedef struct {
    char numero[20]; 
    int CVV;
    float saldo;
} Tarjeta;

void mostrarLibros(Libro *libros, int cuantoslibros) {
    printf("Bienvenido a la libreria!\n");
    printf("Seleccioaejaehnaurgayuna un libro\n\n");   
    for (int e = 0; e < cuantoslibros; e++) {
        printf("%d. Libro: %s\n", e + 1, libros[e].nombre);
    }
}

int main() {
    printf("prueba");
    Libro *libros = malloc(MAX_LIBROS * sizeof(Libro));
    if (libros == NULL) {
        printf("Error al asignar memoria\n");
        return 1;
    }

    printf("antes");
    // Inicialización de libros
    libros[0].nombre = "sonic2";
    strcpy(libros[0].descripcion, "desc");
    libros[0].precioCo = 1.0;
    libros[0].precioAl = 2.0;
    strcpy(libros[0].genero, "sexo");
    printf("despues");

    libros[1].nombre = "sonic3";
    strcpy(libros[1].descripcion, "desc");
    libros[1].precioCo = 1.0;
    libros[1].precioAl = 2.0;
    strcpy(libros[1].genero, "sexo");

    libros[2].nombre = "sonic1";
    strcpy(libros[2].descripcion, "desc");
    libros[2].precioCo = 1.0;
    libros[2].precioAl = 2.0;
    strcpy(libros[2].genero, "sexo");

    // Inicialización de tarjetas de crédito
    Tarjeta tarjetas[MAX_TARJETAS] = {
        {"1234567812345678", 123, 323.39},
        {"9876543298765432", 456, 69.42}
    };

    int cuantoslibros = 3; // Número de libros predefinidos
    int numeroUsuario;
    char opcion;
    
    do {
        mostrarLibros(libros, cuantoslibros);

        printf("\nSeleccioaeaeaeaeana un libro: ");
        scanf("%d", &numeroUsuario);
        printf("\n");

        if(numeroUsuario > cuantoslibros || numeroUsuario <= 0) {
            printf("ERROR: ELIGE UN LIBRO VÁLIDO\n");
            continue;
        }

        printf("\n¡LIBRO SELECCIONADO DE FORMA CORRECTA!\n\n");
        printf("Ficha técnica:\n");
        printf("    Libro seleccionado: %s\n", libros[numeroUsuario - 1].nombre);
        printf("    Descripción: %s\n", libros[numeroUsuario - 1].descripcion);
        printf("    Precio de compra: %.2f\n", libros[numeroUsuario - 1].precioCo);
        printf("    Precio de alquiler: %.2f\n", libros[numeroUsuario - 1].precioAl);

        printf("\n");
        printf("P [pagar]  V [volver]\n");
        scanf(" %c", &opcion);

    } while (opcion == 'V' || opcion == 'v');

    if (opcion == 'P' || opcion == 'p') {
        printf("\nTarjetas registradas:\n");
        for (int i = 0; i < MAX_TARJETAS; i++) {
            printf("Tarjeta %d: Número: %s, CVV: %d\n", i + 1, tarjetas[i].numero, tarjetas[i].CVV);
        }
    }

    free(libros);
    return 0;
}