#include "guateque.h"
#include "sqlite3.h"
#include "../../gui/guateques/guateque.h"
#include <stdio.h>

const char *GUATEQUEDB = "src\\BBDD\\guateque.db"; 

int crear_guateque(Guateque g){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    if (sqlite3_open(GUATEQUEDB, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char *insert = "INSERT INTO GUATEQUE(NOMBRE, DIR, ID_E) VALUES (?, ?, ?, ?)";
    if (sqlite3_prepare_v2(db, insert, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    sqlite3_bind_text(stmt, 1, g.nombre, strlen(g.nombre), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, g.direccion, strlen(g.direccion), SQLITE_STATIC);
    sqlite3_bind

    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error al insertar la pelicula\n");
        return 1;
    } else {
        printf("Pelicula insertada correctamente\n");
        return 0;
    }
}