#include "sqlite3.h"
#include "suicidiosBD.h"
#include "src/gui/suicidios/KillSesion.h"


const char *CINEBD = "src/BBDD/bes.db";

//insertarSuicidio
int insert_muerte(KillSesion *k, Usuario *u)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    if (sqlite3_open(CINEBD, &db) != SQLITE_OK) 
    {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    char* insertK = "INSERT INTO KILLSESION(ID, DIA, MES, ANYO, MUERTE, EDAD, NOMBRE)";
    if (sqlite3_prepare_v2(db, insertK, -1, &stmt, NULL) != SQLITE_OK) 
    {
        printf("Error al preparar la declaración SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    
    sqlite3_bind_int(stmt, 1, u->getId());
    sqlite3_bind_int(stmt, 2, k->getDia());
    sqlite3_bind_int(stmt, 3, k->getMes());
    sqlite3_bind_int(stmt, 4, k->getAnyo());
    sqlite3_bind_text(stmt, 5, k->getTipoMuerte().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 6, u->getEdad());
    sqlite3_bind_text(stmt, 7, u->getNombre().c_str(), -1,SQLITE_STATIC);

    int result =sqlite3_step(stmt);
    if(result != SQLITE_DONE)
    {
        printf("Error al insertar la pelicula\n");
        return 1;
    } else 
    {
        printf("Suicidio insertado correctamente\n");
        return 0;
    }
    
}
Usuario* show_usuarios()
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    if (sqlite3_open(CINEBD, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return NULL;
    }
    char *selectU = "SELECT * FROM KILLSESION";
    if (sqlite3_prepare_v2(db, selectU, -1, &stmt, NULL) != SQLITE_OK) 
    {
        printf("Error al preparar la declaración SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }
    Usuario* usuarios = new Usuario[100];
    if (usuarios == NULL) {
        printf("Error al asignar memoria para los usuarios\n");
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return NULL;
    }
    int r=0;
    while (sqlite3_step(stmt) == SQLITE_ROW) 
    {
        
        *usuarios[r]->getId() = sqlite3_column_int(stmt, 1);


    }
}