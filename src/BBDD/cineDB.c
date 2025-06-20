#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "cineDB.h"


const char *CINEBD = "src/BBDD/bes.db"; // Ruta de la base de datos
// Estructura para almacenar una película


// insertar pelicula 
int insert_pelicula(Pelicula *p){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    if (sqlite3_open(CINEBD, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char *insertP = "INSERT INTO PELICULA(NOMBRE, HORA, DESCRIPCION, CINE, SALIDA, PRECIO, GENERO, DIRECTOR, RATING) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)";
    if (sqlite3_prepare_v2(db, insertP, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    sqlite3_bind_text(stmt, 1, p->titulo, strlen(p->titulo), SQLITE_STATIC);
    sqlite3_bind_double(stmt, 2, p->hora);
    sqlite3_bind_text(stmt, 3, p->descripcion, strlen(p->descripcion), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, p->cine, strlen(p->cine), SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, p->salida);
    sqlite3_bind_double(stmt, 6, p->precio);
    sqlite3_bind_text(stmt, 7, p->genero, strlen(p->genero), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 8, p->director, strlen(p->director), SQLITE_STATIC);
    sqlite3_bind_int(stmt, 9, p->rating);

    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error al insertar la pelicula\n");
        return 1;
    } else {
        printf("Pelicula insertada correctamente\n");
        return 0;
    }
}

// enseñar peliculas 
Pelicula* show_pelicula() {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    if (sqlite3_open(CINEBD, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return NULL;
    }
    // printf("Base de datos abierta\n");

    char *selectP = "SELECT * FROM PELICULA";
    if (sqlite3_prepare_v2(db, selectP, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    Pelicula *peliculas = (Pelicula *)malloc(100 * sizeof(Pelicula));
    if (peliculas == NULL) {
        printf("Error al asignar memoria para las películas\n");
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return NULL;
    }

    int r = 0;
    printf("===================================\n");
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // Asignar memoria dinámica para cada campo
        const unsigned char *titulo = sqlite3_column_text(stmt, 0);
        peliculas[r].titulo = malloc(strlen((const char *)titulo) + 1);
        if (peliculas[r].titulo == NULL) {
            printf("Error al asignar memoria para el título\n");
            break;
        }
        strcpy(peliculas[r].titulo, (const char *)titulo);

        peliculas[r].hora = sqlite3_column_double(stmt, 1);

        const unsigned char *descripcion = sqlite3_column_text(stmt, 2);
        peliculas[r].descripcion = malloc(strlen((const char *)descripcion) + 1);
        if (peliculas[r].descripcion == NULL) {
            printf("Error al asignar memoria para la descripción\n");
            break;
        }
        strcpy(peliculas[r].descripcion, (const char *)descripcion);

        const unsigned char *cine = sqlite3_column_text(stmt, 3);
        peliculas[r].cine = malloc(strlen((const char *)cine) + 1);
        if (peliculas[r].cine == NULL) {
            printf("Error al asignar memoria para el cine\n");
            break;
        }
        strcpy(peliculas[r].cine, (const char *)cine);

        peliculas[r].salida = sqlite3_column_int(stmt, 4);
        peliculas[r].precio = sqlite3_column_double(stmt, 5);

        const unsigned char *genero = sqlite3_column_text(stmt, 6);
        peliculas[r].genero = malloc(strlen((const char *)genero) + 1);
        if (peliculas[r].genero == NULL) {
            printf("Error al asignar memoria para el género\n");
            break;
        }
        strcpy(peliculas[r].genero, (const char *)genero);

        const unsigned char *director = sqlite3_column_text(stmt, 7);
        peliculas[r].director = malloc(strlen((const char *)director) + 1);
        if (peliculas[r].director == NULL) {
            printf("Error al asignar memoria para el director\n");
            break;
        }
        strcpy(peliculas[r].director, (const char *)director);

        peliculas[r].rating = sqlite3_column_int(stmt, 8);

        // printf("Pelicula: %s\n", peliculas[r].titulo);
        r++;
    }

    // Finalizar y cerrar la base de datos
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return peliculas;
}
// enseñar peliculas por cine
Pelicula* peliculas_by_cine(Pelicula *p, char *cine){
    Pelicula *peliculas = (Pelicula *)malloc(100 * sizeof(Pelicula));
    if (peliculas == NULL) {
        printf("Error al asignar memoria para las películas\n");
        return NULL;
    }
    int r = 0;
    for (int i = 0; i < 100; i++) {
        if (strlen(p[i].titulo) == 0) {
            break;
        }
        if (strcmp(p[i].cine, cine) == 0) {
            peliculas[r] = p[i];
            r++;
        }
    }
    return peliculas;
}

// borrar base de datos de pelicula
int borrarbdPelicula(){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    if (sqlite3_open(CINEBD, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char *deleteP = "DELETE FROM PELICULA";
    if (sqlite3_prepare_v2(db, deleteP, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error al borrar la tabla\n");
        return 1;
    } else {
        printf("Peliculas borradas correctamente\n");
        return 0;
    }
}

//insertar critica
int insert_critica(Critica *c){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    if (sqlite3_open(CINEBD, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char *insertC = "INSERT INTO CRITICA(PELICULA, USUARIO, NOTA, RESENA) VALUES (?, ?, ?, ?)";
    if (sqlite3_prepare_v2(db, insertC, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    sqlite3_bind_text(stmt, 1, c->pelicula, strlen(c->pelicula), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, c->usuario, strlen(c->usuario), SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, c->nota);
    sqlite3_bind_text(stmt, 4, c->resena, strlen(c->resena), SQLITE_STATIC);
    

    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error al insertar la crítica\n");
        return 1;
    } else {
        printf("Crítica insertada correctamente\n");
        return 0;
    }
}
// enseñar criticas
Critica* show_critica(){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    if (sqlite3_open(CINEBD, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return NULL;
    }
    // printf("Base de datos abierta\n");

    char *selectC = "SELECT * FROM CRITICA";
    if (sqlite3_prepare_v2(db, selectC, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    Critica *criticas = (Critica *)malloc(100 * sizeof(Critica));
    if (criticas == NULL) {
        printf("Error al asignar memoria para las críticas\n");
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return NULL;
    }

    int r = 0;
    printf("===================================\n");
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // Asignar memoria dinámica para cada campo
        const unsigned char *pelicula = sqlite3_column_text(stmt, 0);
        criticas[r].pelicula = malloc(strlen((const char *)pelicula) + 1);
        if (criticas[r].pelicula == NULL) {
            printf("Error al asignar memoria para la película\n");
            break;
        }
        strcpy(criticas[r].pelicula, (const char *)pelicula);

        const unsigned char *usuario = sqlite3_column_text(stmt, 1);
        criticas[r].usuario = malloc(strlen((const char *)usuario) + 1);
        if (criticas[r].usuario == NULL) {
            printf("Error al asignar memoria para el usuario\n");
            break;
        }
        strcpy(criticas[r].usuario, (const char *)usuario);

        criticas[r].nota = sqlite3_column_int(stmt, 2);

        const unsigned char *resena = sqlite3_column_text(stmt, 3);
        criticas[r].resena = malloc(strlen((const char *)resena) + 1);
        if (criticas[r].resena == NULL) {
            printf("Error al asignar memoria para la reseña\n");
            break;
        }
    }
}
// critica por pelicula
Critica* critica_by_pelicula(Critica *c, char *pelicula){
    Critica *criticas = (Critica *)malloc(100 * sizeof(Critica));
    if (criticas == NULL) {
        printf("Error al asignar memoria para las críticas\n");
        return NULL;
    }
    int r = 0;                                  
    for (int i = 0; i < 100; i++) {
        if (strlen(c[i].pelicula) == 0) {
            break;
        }
        if (strcmp(c[i].pelicula, pelicula) == 0) {
            criticas[r] = c[i];
            r++;
        }
    }
    return criticas;
}
// borrar base de datos de critica
int borrarbdCritica(){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    if (sqlite3_open(CINEBD, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char *deleteC = "DELETE FROM CRITICA";
    if (sqlite3_prepare_v2(db, deleteC, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error al borrar la tabla\n");
        return 1;
    } else {
        printf("Critica borrada correctamente\n");
        return 0;
    }
}


// insertar libro
int insert_libro(Libro *l){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    if (sqlite3_open(CINEBD, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    char *insertL = "INSERT INTO LIBRO(NOMBRE, DESCRIPCION, PCO, PAL, GENERO) VALUES (?, ?, ?, ?, ?)";
    if (sqlite3_prepare_v2(db, insertL, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    sqlite3_bind_text(stmt, 1, l->nombre, strlen(l->nombre), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, l->descripcion, strlen(l->descripcion), SQLITE_STATIC);
    sqlite3_bind_double(stmt, 3, l->precioCo);
    sqlite3_bind_double(stmt, 4, l->precioAl);
    sqlite3_bind_text(stmt, 5, l->genero, strlen(l->genero), SQLITE_STATIC);

    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error al insertar la pelicula\n");
        return 1;
    } else {
        //printf("Pelicula insertada correctamente\n");
        return 0;
    }

}


// enseñar libros 
Libro* show_libro() {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int cantidad = count_libros();
    if (cantidad <= 0) {
        printf("No hay libros en la base de datos.\n");
        return NULL;
    }

    if (sqlite3_open(CINEBD, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    char *selectL = "SELECT * FROM LIBRO";
    if (sqlite3_prepare_v2(db, selectL, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    Libro *libros = (Libro *)malloc(cantidad * sizeof(Libro));
    if (libros == NULL) {
        printf("Error al asignar memoria para los libros\n");
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return NULL;
    }

    int r = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char *nombre = sqlite3_column_text(stmt, 0);
        libros[r].nombre = malloc(strlen((const char *)nombre) + 1);
        strcpy(libros[r].nombre, (const char *)nombre);

        const unsigned char *descripcion = sqlite3_column_text(stmt, 1);
        libros[r].descripcion = malloc(strlen((const char *)descripcion) + 1);
        strcpy(libros[r].descripcion, (const char *)descripcion);

        libros[r].precioAl = sqlite3_column_double(stmt, 2);
        libros[r].precioCo = sqlite3_column_double(stmt, 3);

        const unsigned char *genero = sqlite3_column_text(stmt, 4);
        libros[r].genero = malloc(strlen((const char *)genero) + 1);
        strcpy(libros[r].genero, (const char *)genero);

        r++;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return libros;
}

//contar cuantos libros hay
int count_libros() {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int count = 0;

    if (sqlite3_open(CINEBD, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    const char *countQuery = "SELECT COUNT(*) FROM LIBRO";
    if (sqlite3_prepare_v2(db, countQuery, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración COUNT: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    //printf("LA CUENTA: %d", count);
    return count;
}

// eliminar libro
int delete_libro(Libro *l){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    if (sqlite3_open(CINEBD, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char *deleteL = "DELETE FROM LIBRO WHERE NOMBRE = ?";
    if (sqlite3_prepare_v2(db, deleteL, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, l->nombre, strlen(l->nombre), SQLITE_STATIC);

    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error al borrar el libro\n");
        return 1;
    } else {
        //printf("Libro borrado correctamente\n");
        return 0;
    }
}
// borrar base de datos de libro
int borrarbdLibro(){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    if (sqlite3_open(CINEBD, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char *deleteL = "DELETE FROM LIBRO";
    if (sqlite3_prepare_v2(db, deleteL, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error al borrar la tabla\n");
        return 1;
    } else {
        printf("Libros borrados correctamente\n");
        return 0;
    }
}

// insertar libro en el inventario
int insert_inventario(Libro *l, int dia, int mes, int ano){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    if (sqlite3_open(CINEBD, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    char *insertL = "INSERT INTO INVENTARIO(NOMBRE, DESCRIPCION, PCO, PAL, GENERO, DIA, MES, ANO) VALUES (?, ?, ?, ?, ?, ?, ?, ?)";
    if (sqlite3_prepare_v2(db, insertL, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    sqlite3_bind_text(stmt, 1, l->nombre, strlen(l->nombre), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, l->descripcion, strlen(l->descripcion), SQLITE_STATIC);
    sqlite3_bind_double(stmt, 3, l->precioCo);
    sqlite3_bind_double(stmt, 4, l->precioAl);
    sqlite3_bind_text(stmt, 5, l->genero, strlen(l->genero), SQLITE_STATIC);
    sqlite3_bind_int(stmt, 6, dia);
    sqlite3_bind_int(stmt, 7, mes);
    sqlite3_bind_int(stmt, 8, ano);

    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error al insertar la libro\n");
        return 1;
    } else {
        //printf("libro insertado correctamente\n");
        return 0;
    }

}

Libro* show_inventario() {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    if (sqlite3_open(CINEBD, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return NULL;
    }
    // printf("Base de datos abierta\n");

    char *selectL = "SELECT * FROM INVENTARIO";
    if (sqlite3_prepare_v2(db, selectL, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    Libro *libros = (Libro *)malloc(100 * sizeof(Libro));
    if (libros == NULL) {
        printf("Error al asignar memoria para los libros\n");
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return NULL;
    }

    int r = 0;
    //printf("===================================\n");
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // Asignar memoria dinámica para cada campo
        const unsigned char *nombre = sqlite3_column_text(stmt, 0);
        libros[r].nombre = malloc(strlen((const char *)nombre) + 1);
        if (libros[r].nombre == NULL) {
            printf("Error al asignar memoria para el título\n");
            break;
        }
        strcpy(libros[r].nombre, (const char *)nombre);

        

        const unsigned char *descripcion = sqlite3_column_text(stmt, 1);
        libros[r].descripcion = malloc(strlen((const char *)descripcion) + 1);
        if (libros[r].descripcion == NULL) {
            printf("Error al asignar memoria para la descripción\n");
            break;
        }
        strcpy(libros[r].descripcion, (const char *)descripcion);     
        libros[r].precioAl = sqlite3_column_double(stmt, 2);
        libros[r].precioCo = sqlite3_column_double(stmt, 3);
        // printf("Pelicula: %s\n", peliculas[r].titulo);

        const unsigned char *genero = sqlite3_column_text(stmt, 4);
        libros[r].genero = malloc(strlen((const char *)genero) + 1);
        if (libros[r].genero == NULL) {
            printf("Error al asignar memoria para el género\n");
            break;
        }
        strcpy(libros[r].genero, (const char *)genero);

        r++;
    }

    // Finalizar y cerrar la base de datos
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return libros;
}
// eliminar libro del inventario
int delete_libroInventario(Libro *l){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    if (sqlite3_open(CINEBD, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char *deleteL = "DELETE FROM INVENTARIO WHERE NOMBRE = ?";
    if (sqlite3_prepare_v2(db, deleteL, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, l->nombre, strlen(l->nombre), SQLITE_STATIC);

    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error al borrar el libro\n");
        return 1;
    } else {
        //printf("Libro borrado correctamente\n");
        return 0;
    }
}
int borrarbdInventario(){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    if (sqlite3_open(CINEBD, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char *deleteL = "DELETE FROM INVENTARIO";
    if (sqlite3_prepare_v2(db, deleteL, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error al borrar la tabla\n");
        return 1;
    } else {
        printf("Inventario borrado correctamente\n");
        return 0;
    }
}

int getdiaInventarioPorNombre(const char *nombreLibro) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int dia = -1;  // Usamos -1 para indicar que no se encontró

    if (sqlite3_open(CINEBD, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    const char *query = "SELECT DIA FROM INVENTARIO WHERE NOMBRE = ?";
    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    // Vincula el nombre al parámetro SQL
    if (sqlite3_bind_text(stmt, 1, nombreLibro, -1, SQLITE_STATIC) != SQLITE_OK) {
        printf("Error al vincular el parámetro: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return -1;
    }

    // Ejecutar y obtener el resultado
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        dia = sqlite3_column_int(stmt, 0);
        //printf("Día para '%s': %d\n", nombreLibro, dia);
    } else {
        printf("No se encontro el libro con nombre: %s\n", nombreLibro);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);


    //printf("DIA: %d\n", dia);
    return dia;
}

int getmesInventarioPorNombre(const char *nombreLibro) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int mes = -1;

    if (sqlite3_open(CINEBD, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    const char *query = "SELECT MES FROM INVENTARIO WHERE NOMBRE = ?";
    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    if (sqlite3_bind_text(stmt, 1, nombreLibro, -1, SQLITE_STATIC) != SQLITE_OK) {
        printf("Error al vincular el parámetro: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return -1;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        mes = sqlite3_column_int(stmt, 0);
    } else {
        printf("No se encontro el libro con nombre: %s\n", nombreLibro);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return mes;
}

int getanoInventarioPorNombre(const char *nombreLibro) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int ano = -1;

    if (sqlite3_open(CINEBD, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    const char *query = "SELECT ANO FROM INVENTARIO WHERE NOMBRE = ?";
    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    if (sqlite3_bind_text(stmt, 1, nombreLibro, -1, SQLITE_STATIC) != SQLITE_OK) {
        printf("Error al vincular el parámetro: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return -1;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        ano = sqlite3_column_int(stmt, 0);
    } else {
        printf("No se encontro el libro con nombre: %s\n", nombreLibro);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return ano;
}

int count_inventario() {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int count = 0;

    if (sqlite3_open(CINEBD, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    const char *countQuery = "SELECT COUNT(*) FROM INVENTARIO";
    if (sqlite3_prepare_v2(db, countQuery, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración COUNT: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return count;
}

int insert_tarjeta(Tarjeta t){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    if (sqlite3_open(CINEBD, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char *insertT = "INSERT INTO TARJETA(NUMERO, CVV, SALDO) VALUES (?, ?, ?)";
    if (sqlite3_prepare_v2(db, insertT, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    sqlite3_bind_text(stmt, 1, t.numero, strlen(t.numero), SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, t.CVV);
    sqlite3_bind_double(stmt, 3, t.saldo);
    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error al insertar la tarjeta\n");
        return 1;
    } else {
        printf("Tarjeta insertada correctamente\n");
        return 0;
    }
    sqlite3_finalize(stmt);
}

int count_tarjetas() {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int count = 0;

    if (sqlite3_open(CINEBD, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    const char *countQuery = "SELECT COUNT(*) FROM TARJETA";
    if (sqlite3_prepare_v2(db, countQuery, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración COUNT: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return count;
}

// enseñar tarjetas
Tarjeta* show_tarjeta() {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    if (sqlite3_open(CINEBD, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return NULL;
    }
    // printf("Base de datos abierta\n");

    char *selectT = "SELECT * FROM TARJETA";
    if (sqlite3_prepare_v2(db, selectT, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    Tarjeta *tarjetas = (Tarjeta *)malloc(100 * sizeof(Tarjeta));
    if (tarjetas == NULL) {
        printf("Error al asignar memoria para las tarjetas\n");
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return NULL;
    }

    int r = 0;
    //printf("===================================\n");
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // Asignar memoria dinámica para cada campo
        const unsigned char *numero = sqlite3_column_text(stmt, 0);
        strcpy(tarjetas[r].numero, (const char *)numero);

        tarjetas[r].CVV = sqlite3_column_int(stmt, 1);
        tarjetas[r].saldo = sqlite3_column_double(stmt, 2);
        
        r++;
    }

    // Finalizar y cerrar la base de datos
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return tarjetas;
}
// eliminar tarjeta
int delete_tarjeta(Tarjeta t){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    if (sqlite3_open(CINEBD, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char *deleteT = "DELETE FROM TARJETA WHERE NUMERO = ?";
    if (sqlite3_prepare_v2(db, deleteT, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, t.numero, strlen(t.numero), SQLITE_STATIC);

    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error al borrar la tarjeta\n");
        return 1;
    } else {
        printf("Tarjeta borrada correctamente\n");
        return 0;
    }
}
// borrar base de datos de tarjeta
int borrarbdTarjeta(){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    if (sqlite3_open(CINEBD, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char *deleteT = "DELETE FROM TARJETA";
    if (sqlite3_prepare_v2(db, deleteT, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error al borrar la tabla\n");
        return 1;
    } else {
        printf("Tarjetas borradas correctamente\n");
        return 0;
    }
}
//actualizar saldo tarjeta
int update_saldo(Tarjeta t, double saldo){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    if (sqlite3_open(CINEBD, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char *updateT = "UPDATE TARJETA SET SALDO = ? WHERE NUMERO = ?";
    if (sqlite3_prepare_v2(db, updateT, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_double(stmt, 1, saldo);
    sqlite3_bind_text(stmt, 2, t.numero, strlen(t.numero), SQLITE_STATIC);

    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error al actualizar el saldo\n");
        return 1;
    } else {
        //printf("Saldo actualizado correctamente\n");
        return 0;
    }
}
