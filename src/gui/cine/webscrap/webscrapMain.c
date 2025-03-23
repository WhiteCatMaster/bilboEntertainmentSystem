#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "webscrapMain.h"
#include "../../../BBDD/cineDB.h" // Aquí se asume que insertarPelicula está definida

void pyAlhondiga(void)
{
    FILE *fp;
    char path[1035];
    Pelicula **peliculas = NULL; // Array dinámico de punteros a Pelicula
    int r = 0;

    // Ejecutar el comando de Python
    fp = popen("python alhondiga.py --titulos", "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        return;
    }

    // Leer la salida del comando y crear una nueva película por cada título
    while (fgets(path, sizeof(path), fp) != NULL) {
        path[strcspn(path, "\n")] = '\0'; // Eliminar el carácter de nueva línea

        // Redimensionar el array dinámico para agregar una nueva película
        peliculas = realloc(peliculas, sizeof(Pelicula *) * (r + 1));
        if (peliculas == NULL) {
            printf("Error al asignar memoria\n");
            pclose(fp);
            return;
        }

        // Crear una nueva película y asignar el título
        peliculas[r] = malloc(sizeof(Pelicula));
        if (peliculas[r] == NULL) {
            printf("Error al asignar memoria para la película\n");
            pclose(fp);
            return;
        }
        snprintf(peliculas[r]->titulo, sizeof(peliculas[r]->titulo), "%s", path);

        // Insertar la película en la base de datos
        if (insertarPelicula(peliculas[r]) != 0) {
            printf("Error al insertar la película en la base de datos: %s\n", peliculas[r]->titulo);
        } else {
            printf("Película insertada en la base de datos: %s\n", peliculas[r]->titulo);
        }

        r++;
    }

    // Cerrar el archivo
    pclose(fp);

    // Liberar la memoria de cada película
    for (int i = 0; i < r; i++) {
        free(peliculas[i]);
    }

    // Liberar el array dinámico
    free(peliculas);
}

int main(void)
{
    pyAlhondiga();
    return 0;
}