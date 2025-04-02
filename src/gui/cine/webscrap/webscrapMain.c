#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "webscrapMain.h"
#include "../../../BBDD/cineDB.h" // Aquí se asume que insertarPelicula está definida
int ccsave = 0;
int ccsaveAPI = 0; 

void pyAlhondiga(void)
{
    printf("Ejecutando el script de Python...\n");
    FILE *fp;
    char path[1035];
    Pelicula **peliculas = NULL; // Array dinámico de punteros a Pelicula
    int r = 0;
    borrarbdPelicula(); // Borrar la base de datos de películas

    // Ejecutar el comando de Python
    fp = popen("python src/gui/cine/webscrap/alhondiga.py --titulos", "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        return;
    }
    printf("Comando ejecutado\n");
    // Leer la salida del comando y crear una nueva película por cada título
    while (fgets(path, sizeof(path), fp) != NULL) {
        // printf("Leyendo linea: %s", path);
        path[strcspn(path, "\n")] = '\0'; // Eliminar el carácter de nueva línea

        // Redimensionar el array dinámico para agregar una nueva película
        peliculas = realloc(peliculas, sizeof(Pelicula *) * (r + 1));
        if (peliculas == NULL) {
            printf("Error al asignar memoria\n");
            pclose(fp);
            return;
        }
        // printf("Memoria asignada\n");
        // Crear una nueva película y asignar el título
        peliculas[r] = malloc(sizeof(Pelicula));
        if (peliculas[r] == NULL) {
            printf("Error al asignar memoria para la película\n");
            pclose(fp);
            return;
        }

        // Allocate memory for the title
        peliculas[r]->titulo = malloc(strlen(path) + 1);
        if (peliculas[r]->titulo == NULL) {
            printf("Error al asignar memoria para el título\n");
            free(peliculas[r]);
            pclose(fp);
            return;
        }
        strcpy(peliculas[r]->titulo, path);
        peliculas[r]->hora = 0.0;
        peliculas[r]->descripcion = "No disponible";
        peliculas[r]->cine = "Alhóndiga";
        peliculas[r]->salida = 0;
        peliculas[r]->precio = 0.0;
        peliculas[r]->genero = "No disponible";
        peliculas[r]->director = "No disponible";
        peliculas[r]->rating = 0;
        peliculas[r]->id = 0;
        printf("Pelicula creada\n");
        ccsave +=1;

        // Insertar la película en la base de datos
        if (insert_pelicula(peliculas[r]) != 0) {
            printf("Error al insertar la película en la base de datos: %s\n", peliculas[r]->titulo);
        } else {
            // printf("Película insertada en la base de datos: %s\n", peliculas[r]->titulo);
        }
        // printf("Pelicula insertada\n");
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
void consultorAPI(void)
{
    printf("Ejecutando el script de Python...\n");
    FILE *fp;
    char path[1035];
    fp = popen("python src/gui/cine/webscrap/movies.py upstream", "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        return;
    }
    while (fgets(path, sizeof(path), fp) != NULL) {
        printf("%s", path);
    }
    pclose(fp);
}
/*
int main(void)
{
    pyAlhondiga();
    return 0;
}
    */