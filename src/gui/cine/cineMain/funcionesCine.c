#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionesCine.h"
#include "../../../BBDD/cineDB.h"
#include "../webscrap/webscrapMain.h"


void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/*
void filtrarCine(char *cine[])
{
    clear_screen();
    printf("1--> Alhondiga");
    printf("2--> Cinesa");
    printf("3--> Upcomming Global");
    char i = getchar();
    if (i == '1')
    {

    }else if (i == '2')
    {

    }else if (i=='3')
    {

    }else
    {

    }



}

*/
/*

void filtraje(char *cine[])
{
    char i = 's';
    while (i != '1' && i != '2')
    {
        clear_screen();
        printf("elije una opcion: \n");
        printf("1.-->  filtrar x cine\n");
        printf("2.-->  filtrar x pelicula\n");
        i = getchar();
        if (i == '1')
        {
            printf("filtrar x cine\n");
            filtrarCine(cine);

        }
        else if (i == '2')
        {
            printf("filtrar x pelicula\n");
            filtrarPelicula();
        }
        else
        {
            printf("opcion no valida\n");
        }
    }
}
*/
// elegir numero de entradas
int elegirNEntradas(int altura, int anchura) {
    int nEntradas;
    printf("Cuantas entradas quieres comprar?: ");
    scanf("%d", &nEntradas);
    while (nEntradas > altura * anchura || nEntradas <= 0) {
        printf("No hay suficientes asientos disponibles. Intenta de nuevo: ");
        scanf("%d", &nEntradas);
    }
    return nEntradas;
}

void elegirAsientos(int nEntradas, char **matrizAsientos, int altura, int anchura) {
    clear_screen();
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("                                                              pantalla\n");
    printf("------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < anchura; j++) {
            matrizAsientos[i][j] = '0';
        }
    }
    for (int i = 0; i < altura; i++) {
        printf("%d  ", i );
        for (int j = 1; j < anchura; j++) {
            if (i == 0) {
                if (j > 9) {
                    printf("%d ", j);
                } else {
                    printf("%d  ", j);
                }
            } else {
                printf("%c  ", matrizAsientos[i][j]);
            }
        }
        printf("\n");
    }
    for (int i = 0; i < nEntradas; i++) {
        int fila, columna;
        printf("Elige numero de fila: \n");
        scanf("%d", &fila);
        printf("Elige numero de columna: \n");
        scanf("%d", &columna);

        if (fila >= 0 && fila < altura && columna >= 0 && columna < anchura) {
            if (matrizAsientos[fila][columna] == '0') {
                matrizAsientos[fila][columna] = 'x';
                printf("Asiento [%d, %d] reservado.\n", fila, columna);
            } else {
                printf("El asiento [%d, %d] ya está ocupado. Elige otro asiento.\n", fila, columna);
                i--;  // Decrement i to retry the current seat selection
            }
        } else {
            printf("Asiento [%d, %d] fuera de rango. Elige otro asiento.\n", fila, columna);
            i--;  // Decrement i to retry the current seat selection
        }
    }
}


int comprarEntradas() {
    char e = 'e'; // Inicializar la variable de control del bucle
    int pelicula;
    int nentradas;
    int altura = 5;
    int anchura = 40;
    char **matrizAsientos;

    // Allocate and initialize matrizAsientos
    matrizAsientos = (char **)calloc(altura, sizeof(char *));
    for (int i = 0; i < altura; i++) {
        matrizAsientos[i] = (char *)calloc(anchura, sizeof(char));
    }

    // Allocate and initialize entradas
    char **entradas = (char **)calloc(100, sizeof(char *));
    for (int i = 0; i < 100; i++) {
        entradas[i] = (char *)calloc(100, sizeof(char));
    }

    while (e != '0') {
        pelicula = 0;
        //printf("===================================\n");
        //printf("alli");
        Pelicula *peli = show_pelicula();
        //printf("aqui");
        if (peli == NULL) {
            printf("No hay películas disponibles\n");
            return 1;
        }
        
        printf("===================================\n");
        for (pelicula = 0; pelicula < ccsave; pelicula++) {
            if (strlen(peli[pelicula].titulo) == 0) {
                break; // Detener si no hay más películas
            }
            strcpy(entradas[pelicula], peli[pelicula].titulo);
        }

        printf("ELIGE UNA PELICULA: \n");
        printf("===================================\n");
        for (int i = 0; i < 100; i++) {
            if (strlen(entradas[i]) == 0) {
                break;
            }
            printf("(%d): --> %s <-- \n", i + 1, entradas[i]);
        }

        printf("INTRODUCE EL NUMERO DE LA PELICULA: ");
        if (scanf("%d", &pelicula) != 1 || pelicula < 1 || pelicula > 100) {
            printf("Entrada no válida. Inténtalo de nuevo.\n");
            while (getchar() != '\n'); // Limpiar el buffer de entrada
            continue;
        }
        pelicula--; // Ajustar para índices basados en cero

        if (pelicula >= 0 && pelicula < 100 && strlen(entradas[pelicula]) > 0) {
            nentradas = elegirNEntradas(altura, anchura);
            elegirAsientos(nentradas, matrizAsientos, altura, anchura);
            printf("Ticket de compra\n");
            printf("Película: %s\n", entradas[pelicula]);
            printf("Asientos: %i \n", nentradas);
            printf("Pulsa 'e' para seguir comprando o '0' para salir: ");
            while (getchar() != '\n'); // Limpiar el buffer de entrada
            scanf(" %c", &e); // Leer la opción del usuario
        } else {
            printf("No has elegido ninguna película válida\n");
            clear_screen();
        }
    }

    // Free allocated memory
    for (int i = 0; i < altura; i++) {
        free(matrizAsientos[i]);
    }
    free(matrizAsientos);

    for (int i = 0; i < 100; i++) {
        free(entradas[i]);
    }
    free(entradas);

    return 0;
}