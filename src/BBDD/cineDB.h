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
    char* resena;
} Critica;

typedef struct {
    char *nombre;
    char *descripcion;
    float precioCo;
    float precioAl;
    char *genero;
} Libro;

int  insert_pelicula(Pelicula *p);
Pelicula* show_pelicula(void);
Pelicula* peliculas_by_cine(Pelicula *p, char *cine);
int borrarbdPelicula();
int insert_critica(Critica *c);
Critica* show_critica(void);
Critica* critica_by_pelicula(Critica *c, char *pelicula);
Critica* critica_by_usuario(Critica *c, char *usuario);
int borrarbdCritica();
int insert_libro(Libro *l);
int show_libro(void);
int delete_libro(Libro *l);

#endif // CINE_DB_H