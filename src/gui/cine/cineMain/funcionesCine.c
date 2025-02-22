#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionesCine.h"

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// elegir numero de entradas
int elegirNEntradas(){
    int nEntradas;
    printf("Cuantas entradas quieres comprar?: ");
    scanf("%d", &nEntradas);
    return nEntradas;
}
int elegirAsientos(int nEntradas){
    int altura = 5;
    int anchura = 40;
    typedef struct {
        int fila;
        int columna;
    } Asiento;
    Asiento asiento1 = {0, 0};
    char matrizAsientos[altura][anchura];
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("                                                              pantalla\n");
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < altura; i++) {

        for (int j = 0; j < anchura; j++) {
            matrizAsientos[i][j] = 0;
        }
    }
    for (int i = 0; i < altura; i++) {
        printf("%d  ", i);
        for (int j = 0; j < anchura; j++) {
            if (i == 0) {
                if (j>9){
                    printf("%d ", j);
                }
                else
                {
                    printf("%d  ", j);
                }
            }
            else
            {
                printf("%d  ", matrizAsientos[i][j]);
            }

        }
        printf("\n");
    }
    for (int i=0; i<nEntradas; i++){
        printf("Elige el asiento %d: ", i);
        printf("fila: ");
        asiento1.fila = getchar();
        printf("columna: ");
        asiento1.columna = getchar();

        if (matrizAsientos[asiento1.fila][asiento1.columna] == '0'){
            matrizAsientos[asiento1.fila][asiento1.columna] = 'x';
        }
        else{
            printf("El asiento ya esta ocupado\n");
            i--;
        }
    }


    return 0;
}
// elegir pelicula
int comprarEntradas()
{
    char e = 'e';
    int pelicula;
    char entradas[100][100];
    int nentradas;
    while(e != '0'){

        pelicula='1';
        strcpy(entradas[0], "Han Solo");
        strcpy(entradas[1], "Indiana Jones");
        strcpy(entradas[2], "Rick Deckard");
        strcpy(entradas[3], "Jack Ryan");
        
        printf("Elige una pelicula\n");
        printf("===================================\n");
        for (int i = 0; i < 100 ; i++)
        {
            if (strlen(entradas[i]) == 0) {
                break;
            }
            printf("(%d): --> %s <-- \n", i, entradas[i]);
        }
        pelicula = getchar() - '0';
        if (pelicula > 0 && pelicula < 4)
        {
            nentradas = elegirNEntradas();
            elegirAsientos(nentradas);

        }
        else
        {
            printf("No has elegido ninguna pelicula\n");
            clear_screen();


        }
    }

    printf("Has elegido %s\n", entradas[pelicula]);

    return 0;
}