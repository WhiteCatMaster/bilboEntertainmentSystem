#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "cineDB.h"


const char *CINEBD = "src\\BBDD\\cine.db"; // Ruta de la base de datos
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
Pelicula* show_pelicula(){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    if (sqlite3_open(CINEBD, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
    }
    char *selectP = "SELECT * FROM PELICULA";
    if (sqlite3_prepare_v2(db, selectP, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        ;
    }
    Pelicula *peliculas = (Pelicula *)malloc(100 * sizeof(Pelicula));
    int r = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {

        strcpy(peliculas[r].titulo, sqlite3_column_text(stmt, 0));
        peliculas[r].hora = sqlite3_column_double(stmt, 1);
        strcpy(peliculas[r].descripcion , sqlite3_column_text(stmt, 2));
        strcpy(peliculas[r].cine , sqlite3_column_text(stmt, 3));
        peliculas[r].salida = sqlite3_column_int(stmt, 4);
        peliculas[r].precio = sqlite3_column_double(stmt, 5);
        strcpy(peliculas[r].genero , sqlite3_column_text(stmt, 6));
        strcpy(peliculas[r].director , sqlite3_column_text(stmt, 7));
        peliculas[r].rating = sqlite3_column_int(stmt, 8);
        r++;
    }

    return peliculas;

}