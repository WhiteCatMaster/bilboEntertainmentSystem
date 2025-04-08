#include "guateque.h"
#include "guatequeDB.h"
#include "sqlite3.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char *GUATEQUEDB = "guateque.db"; 


int insertar_guateque(Guateque g){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    if (sqlite3_open(GUATEQUEDB, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char *insert = "INSERT OR IGNORE INTO GUATEQUE(ID_G, NOMBRE, DIRECCION) VALUES (?, ?, ?);";
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
        printf("Error al insertar el guateque %s\n", g.nombre);
        return 1;
    } else {
        printf("Guateque insertada correctamente\n");
        return 0;
    }
}

int insertar_evento(Evento e){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    if (sqlite3_open(GUATEQUEDB, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char *insert = "INSERT OR IGNORE INTO EVENTO(ID_E, NOMBRE, PRECIO, FECHA, DESCRIPCION, ID_G) VALUES (?, ?, ?, ?, ?, ?);";
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
    sqlite3_bind_int(stmt, 6, e.idg);

    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error al insertar el evento %s\n", e.nombre);
        return 1;
    } else {
        printf("Evento insertada correctamente\n");
        return 0;
    }
}

int contar_guateques(){
    int nguateques = 0;
    sqlite3 *db;
    sqlite3_stmt *stmt;
    if (sqlite3_open(GUATEQUEDB, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    char *select = "SELECT * FROM GUATEQUE;";
    if (sqlite3_prepare_v2(db, select, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }
    

    while(SQLITE_ROW == sqlite3_step(stmt)){
        nguateques++;
    }
    
    // Finalizar y cerrar la base de datos
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    //printf("guatequeDB:contar_guateques.INFO: %d\n",nguateques);
    return nguateques;
}

int contar_eventos(){
    int neventos = 0;
    sqlite3 *db;
    sqlite3_stmt *stmt;
    if (sqlite3_open(GUATEQUEDB, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    char *select = "SELECT * FROM EVENTO;";
    if (sqlite3_prepare_v2(db, select, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }
    

    while(SQLITE_ROW == sqlite3_step(stmt)){
        neventos++;
    }
    
    // Finalizar y cerrar la base de datos
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return neventos;
}

int contar_eventos_por_guateque(int id){
    int neventos = 0;
    sqlite3 *db;
    sqlite3_stmt *stmt;
    if (sqlite3_open(GUATEQUEDB, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    char *select = "SELECT * FROM EVENTO WHERE ID_G=?;";

    //char *select = "SELECT COUNT (ID_E) FROM EVENTO WHERE ID_G=?;";
    if (sqlite3_prepare_v2(db, select, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }
    sqlite3_bind_int(stmt,1, id);
    //sqlite3_bind_int(stmt,1, id);

    //neventos=sqlite3_step(stmt);

    while (sqlite3_step(stmt) != SQLITE_DONE) { neventos++; }
    
    // Finalizar y cerrar la base de datos
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return neventos;
}

Evento* get_eventos(){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    if (sqlite3_open(GUATEQUEDB, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    char *select = "SELECT * FROM EVENTO";
    if (sqlite3_prepare_v2(db, select, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

  

    int neventos = contar_eventos();

    //printf("guatequeDB:get_eventos:INFO neventos = %d\n",neventos);

    Evento *eventos = malloc(neventos * sizeof(Evento));
    if (eventos == NULL) {
        printf("Error al asignar memoria\n");
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return NULL;
    }

    for (int i = 0; i < neventos && sqlite3_step(stmt) == SQLITE_ROW; i++)
    {
        eventos[i].id = sqlite3_column_int(stmt, 0); 

        char* nombre = (char *) sqlite3_column_text(stmt, 1);
        eventos[i].nombre = malloc(strlen(nombre)+1);
        strcpy(eventos[i].nombre, nombre);

        //printf("guatequeDB:get_eventos:INFO eventos[%d].nombre = %s\n",i,eventos[i].nombre);

        eventos[i].precio = sqlite3_column_double(stmt, 2);

        //printf("guatequeDB:get_eventos:INFO eventos[%d].precio = %f\n",i,eventos[i].precio);

        char* fecha = (char *) sqlite3_column_text(stmt, 3);
        eventos[i].fecha = malloc(strlen(fecha)+1);
        strcpy(eventos[i].fecha, fecha);

        //printf("guatequeDB:get_eventos:INFO eventos[%d].fecha = %s\n",i,eventos[i].fecha);

        char* descripcion = (char *) sqlite3_column_text(stmt, 4);
        eventos[i].descripcion = malloc(strlen(descripcion)+1);
        strcpy(eventos[i].descripcion, descripcion);

        //printf("guatequeDB:get_eventos:INFO eventos[%d].descripcion = %s\n",i,eventos[i].descripcion);
        
        eventos[i].idg = sqlite3_column_int(stmt, 5);

        //printf("guatequeDB:get_eventos:INFO eventos[%d].idg = %d\n",i,eventos[i].idg);

    }
    
    // Finalizar y cerrar la base de datos
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return eventos;
}

Guateque* get_guateques() {
    sqlite3 *db;
    sqlite3_stmt *stmt;

// Abrimos DB    
    if (sqlite3_open(GUATEQUEDB, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return NULL;
    }
// Recolectamos todos los Guateques
    char *select = "SELECT * FROM GUATEQUE";
    if (sqlite3_prepare_v2(db, select, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }
// Reservamos memoria para los Guateques
    int nguateques = contar_guateques();
    Guateque *guateques = malloc(nguateques * sizeof(Guateque));
    if (guateques == NULL) {
        printf("Error al asignar memoria\n");
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return NULL;
    }
// Recorremos el array hasta el número de Guateques o que haya error
    for (int i = 0; i < nguateques && sqlite3_step(stmt) == SQLITE_ROW; i++)
    {
        int ultevento = 0;
        int id = sqlite3_column_int(stmt, 0);
        guateques[i].id = id; 
        //Comprobamos el número de eventos
        //int neventos = contar_eventos_por_guateque(id);
        int neventos = contar_eventos();

        

        char* nombre = (char *) sqlite3_column_text(stmt, 1);
        guateques[i].nombre = malloc(strlen(nombre)+1);
        strcpy(guateques[i].nombre, nombre);

        //printf("guatequeDB:get_guateques:INFO nombre(%d) = %s\n",i,nombre);

        char* direccion = (char *) sqlite3_column_text(stmt, 2);
        guateques[i].direccion = malloc(strlen(direccion)+1);
        strcpy(guateques[i].direccion, direccion);

        //printf("guatequeDB:get_guateques:INFO direccion(%d) = %s\n",i,direccion);
        
        guateques[i].eventos = malloc(neventos*sizeof(Evento));
        
        Evento* eventos = get_eventos(guateques[i].id); // Obtenemos todos los eventos
        
        for (int j = 0; j < neventos; j++)
        {
            if(eventos[j].idg == guateques[i].id){
                guateques[i].eventos[ultevento] = eventos[j];
                //printf("guatequeDB:get_guateques:INFO Asignamos a guateque(%d) en el índice (%d) el evento con id (%d)\n",i,ultevento,j);
                ultevento++;
            }
        }
        guateques[i].neventos = ultevento;
        //printf("guatequeDB:get_guateques:INFO neventos(%d) = %d\n",i,guateques[i].neventos);
    }

    // Finalizar y cerrar la base de datos
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return guateques;
}

int obtenerIdGuateque(){

    sqlite3 *db;
    sqlite3_stmt *stmt;
    if (sqlite3_open(GUATEQUEDB, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    char *select = "SELECT ID_G FROM GUATEQUE ORDER BY ID_G DESC LIMIT 1;";
    if (sqlite3_prepare_v2(db, select, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    int max = sqlite3_step(stmt);
    

    // Finalizar y cerrar la base de datos
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return max + 1;
}

int obtenerIdEvento(){

    sqlite3 *db;
    sqlite3_stmt *stmt;
    if (sqlite3_open(GUATEQUEDB, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    char *select = "SELECT ID_E FROM EVENTO ORDER BY ID_G DESC LIMIT 1;";
    if (sqlite3_prepare_v2(db, select, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    int max = sqlite3_step(stmt);
    

    // Finalizar y cerrar la base de datos
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return max + 1;
}

int eliminar_evento(Evento e){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    if (sqlite3_open(GUATEQUEDB, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char *insert = "DELETE FROM EVENTO WHERE ID_E = ?;";
    if (sqlite3_prepare_v2(db, insert, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la declaración SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    sqlite3_bind_int(stmt, 1, e.id);

    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error al eliminar el evento %s\n", e.nombre);
        return 1;
    } else {
        printf("Evento eliminado correctamente\n");
        return 0;
    }
}