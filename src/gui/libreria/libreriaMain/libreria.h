#ifndef LIBRERIA_H_
#define LIBRERIA_H_
#include "../../../BBDD/cineDB.h"

typedef struct {
    char numero[20]; 
    int CVV;
    float saldo;
} Tarjeta;

int mostrarLibrosDisponibles();
int unLibro(Libro *libros, int num);
void leer_csv(const char *filename);
Libro pagarTarjetas(Tarjeta **tarjetas, int numlibro, int numtarjetas);

#endif