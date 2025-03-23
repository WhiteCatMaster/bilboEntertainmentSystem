#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "cineDB.h"

const char *CINEBD = "cine.db";

// Estructura para almacenar una película


// insertar pelicula 
void insert_pelicula(Pelicula *p){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    sqlite3_open(CINEBD, &db);

    char *insertP = "INSERT INTO peliculas (titulo, hora, descripcion, cine, salida, precio, genero, director, rating) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)";
    sqlite3_prepare_v2(db, insertP, -1, &stmt, NULL);
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
    } else {
        printf("Pelicula insertada correctamente\n");
    }
}

