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

typedef struct {
    char *pelicula;
    char *usuario;
    int nota;
    char* reseña;
} Critica;

int  insert_pelicula(Pelicula *p);
Pelicula* show_pelicula();
Pelicula* peliculas_by_cine(Pelicula *p, char *cine);
int borrarbdPelicula();
int insert_critica(Critica *c);
Critica* show_critica();
Critica* critica_by_pelicula(Critica *c, char *pelicula);
Critica* critica_by_usuario(Critica *c, char *usuario);
int borrarbdCritica();

#endif // CINE_DB_H