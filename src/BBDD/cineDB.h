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

typedef struct {
    char numero[20];
    int CVV;
    float saldo;
}Tarjeta;

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
Libro* show_libro(void);
int delete_libro(Libro *l);
int borrarbdLibro();
int insert_inventario(Libro *l, int dia, int mes, int ano);
Libro* show_inventario(void);
int delete_libroInventario(Libro *l);
int borrarbdInventario();
int insert_tarjeta(Tarjeta t);
Tarjeta* show_tarjeta(void);
int delete_tarjeta(Tarjeta t);
int borrarbdTarjeta();
int update_saldo(Tarjeta t, double saldo);
int count_tarjetas();
int count_libros();
int count_inventario();
int getdiaInventarioPorNombre(const char *nombreLibro);
int getmesInventarioPorNombre(const char *nombreLibro);
int getanoInventarioPorNombre(const char *nombreLibro);

#endif // CINE_DB_H