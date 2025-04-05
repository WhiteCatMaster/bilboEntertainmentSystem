#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../BBDD/cineDB.h"
#define CINE_DB_H

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

        // Usar ";" como delimitador
        nombre = strtok(line, ";");
        descripcion = strtok(NULL, ";");
        precioCo = atof(strtok(NULL, ";"));
        precioAl = atof(strtok(NULL, ";"));
        genero = strtok(NULL, ";\n");
        //printf("Nombre: %s\nDescripcion: %s\nPrecioCompra: %.2f\nPrecioAlquiler: %.2f\nGenero: %s\n\n",nombre, descripcion, precioCo, precioAl, genero);
        Libro lib;
        lib.nombre =nombre;
        lib.descripcion= descripcion;
        lib.precioCo = precioCo;
        lib.precioAl = precioAl; 
        lib.genero= genero;

        insert_libro(&lib); // Insertar el libro en la base de datos

        //printf("Nombre: %s\nDescripcion: %s\nPrecioCompra: %.2f\nPrecioAlquiler: %.2f\nGEEEEnero: %s\n\n", lib.nombre, lib.descripcion, lib.precioCo, lib.precioAl, lib.genero);
    }

    fclose(file);
}

int main() {
    printf("Leyendo CSV...\n");
    leer_csv("C:/Users/aitor.sagarduy/Downloads/LibrosBien.csv");
    printf("CSV leído correctamente.\n");
    Libro *sonic;
    
    printf("dale: %s\n", show_libro()[0].nombre);
    
    printf("EMPATIA222.\n");


    printf("porno de enanos");

   // printf("libros: %s\n", libross[0].nombre);
    printf("EMPATIA3.\n");
    return 0;
}
