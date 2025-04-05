#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../BBDD/cineDB.h"

#define MAX_LINE 1024

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

        Libro lib;

        // Usar ";" como delimitador
        nombre = strtok(line, ";");
        descripcion = strtok(NULL, ";");
        precioCo = atof(strtok(NULL, ";"));
        precioAl = atof(strtok(NULL, ";"));
        genero = strtok(NULL, ";\n");

        lib.nombre = nombre;
        lib.descripcion = descripcion;
        lib.precioCo = precioCo;
        lib.precioAl = precioAl; 
        lib.genero = genero; 

        insert_libro(&lib);

        // Verificar que todos los valores se leyeron correctamente
        if (nombre && descripcion && genero) {
            printf("Nombre: %s\nDescripcion: %s\nPrecioCompra: %.2f\nPrecioAlquiler: %.2f\nGeeeenero: %s\n\n",
                   nombre, descripcion, precioCo, precioAl, genero);
        } else {
            printf("Error al leer una línea.\n");
        }
    }

    fclose(file);
}

int main() {
    leer_csv("C:/Users/aitor.sagarduy/Downloads/LibrosBien.csv");
    printf("sexo");

    return 0;
}


