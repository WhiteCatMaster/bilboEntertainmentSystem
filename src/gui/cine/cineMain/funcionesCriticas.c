#include "funcionesCine.h"
#include "../../../BBDD/cineDB.h"
#include "funcionesCriticas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ensenar_criticas() {
    int e = 0;
    while (e == 0) {
        Pelicula *pelicula = show_pelicula();
        for (int i = 0; i < 100; i++) {
            if (strlen(pelicula[i].titulo) == 0) {
                break;
            }
            printf("Peli: %s\n", pelicula[i].titulo);
        }

        char peliculaElegida[100];
        printf("Escribe el nombre de la pelicula de la que quieres ver las criticas: ");
        while (getchar() != '\n'); // Limpiar el buffer de entrada
        fgets(peliculaElegida, sizeof(peliculaElegida), stdin);
        peliculaElegida[strcspn(peliculaElegida, "\n")] = '\0'; // Eliminar el carácter de nueva línea

        Critica *critica = show_critica();
        Critica *criticas = critica_by_pelicula(critica, peliculaElegida);
        for (int i = 0; i < 100; i++) {
            if (strlen(criticas[i].pelicula) == 0) {
                break;
            }
            printf("Critica de %s: %s\n", criticas[i].usuario, criticas[i].resena);
        }

        printf("Añadir critica (y/N): ");
        while (getchar() != '\n'); // Limpiar el buffer de entrada
        char opcion = getchar();
        if (opcion == 'y' || opcion == 'Y') {
            Critica nuevaCritica;
            printf("Escribe tu nombre: ");
            while (getchar() != '\n'); // Limpiar el buffer de entrada
            fgets(nuevaCritica.usuario, sizeof(nuevaCritica.usuario), stdin);
            nuevaCritica.usuario[strcspn(nuevaCritica.usuario, "\n")] = '\0'; // Eliminar el carácter de nueva línea

            printf("Escribe tu critica: ");
            fgets(nuevaCritica.resena, sizeof(nuevaCritica.resena), stdin);
            nuevaCritica.resena[strcspn(nuevaCritica.resena, "\n")] = '\0'; // Eliminar el carácter de nueva línea

            insert_critica(&nuevaCritica);
        }

        printf("Quieres ver más criticas? (y/N): ");
        while (getchar() != '\n'); // Limpiar el buffer de entrada
        char c = getchar();
        if (c == 'N' || c == 'n') {
            e = 1;
        }
    }
}