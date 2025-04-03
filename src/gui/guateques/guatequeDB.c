#include "guatequeDB.h"
#include "sqlite3.h"
#include "guateque.h"
#include <stdio.h>
#include <string.h>

const char *GUATEQUEDB = "src\\BBDD\\guateque.db"; 

int insertar_guateque(Guateque g){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    if (sqlite3_open(GUATEQUEDB, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char *insert = "INSERT INTO GUATEQUE(ID_G, NOMBRE, DIR) VALUES (?, ?, ?)";
    if (sqlite3_prepare_v2(db, insert, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    sqlite3_bind_int(stmt, 1, g.id);
    sqlite3_bind_text(stmt, 2, g.nombre, strlen(g.nombre), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, g.direccion, strlen(g.direccion), SQLITE_STATIC);

    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error al insertar el guateque\n");
        return 1;
    } else {
        printf("Guateque insertada correctamente\n");
        return 0;
    }
}

int insertar_evento(Evento e, Guateque g){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    if (sqlite3_open(GUATEQUEDB, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char *insert = "INSERT INTO EVENTO(ID_E, NOMBRE, PRECIO, FECHA, DESCRIPCION, ID_G) VALUES (?, ?, ?, ?, ?, ?)";
    if (sqlite3_prepare_v2(db, insert, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    sqlite3_bind_int(stmt, 1, e.id);
    sqlite3_bind_text(stmt, 2, e.nombre, strlen(e.nombre), SQLITE_STATIC);
    sqlite3_bind_double(stmt,3, e.precio);
    sqlite3_bind_text(stmt, 4, e.fecha, strlen(e.fecha), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, e.descripcion, strlen(e.descripcion), SQLITE_STATIC);
    sqlite3_bind_int(stmt, 6, g.id);

    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error al insertar el guateque\n");
        return 1;
    } else {
        printf("Guateque insertada correctamente\n");
        return 0;
    }
}