#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "cineDB.h"


const char *CINEBD = "src\\BBDD\\bes.db"; // Ruta de la base de datos
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
        printf("Tabla borrada correctamente\n");
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
        printf("Tabla borrada correctamente\n");
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
        printf("Pelicula insertada correctamente\n");
        return 0;
    }

}


// enseñar libros 
Libro* show_libro() {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    if (sqlite3_open(CINEBD, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return NULL;
    }
    // printf("Base de datos abierta\n");

    char *selectL = "SELECT * FROM LIBRO";
    if (sqlite3_prepare_v2(db, selectL, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    Libro *libros = (Libro *)malloc(100 * sizeof(Libro));
    if (libros == NULL) {
        printf("Error al asignar memoria para las películas\n");
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return NULL;
    }

    int r = 0;
    printf("===================================\n");
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
        printf("Libro borrado correctamente\n");
        return 0;
    }
}
