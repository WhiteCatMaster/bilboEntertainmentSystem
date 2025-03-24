#ifndef CINE_DB_H
#define CINE_DB_H

typedef struct {
    char *titulo;
    float hora;
    char *descripcion;
    char *cine;
    int salida;
    float precio;
    char *genero;
    char *director;
    int rating;
    int id;
} Pelicula;

void insert_pelicula(Pelicula *p);


#endif // CINE_DB_H