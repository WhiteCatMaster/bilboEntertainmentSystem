#ifndef LIBRERIA_H_
#define LIBRERIA_H_
#include "../../../BBDD/cineDB.h"

int mostrarLibrosDisponibles();
int unLibro(Libro *libros, int num);
void leer_csv(const char *filename);
Libro pagarTarjetas(int numlibro, int numtarjetas);
void cargarTarjetas(Tarjeta **tarjetas, int cuantasTarjetas);
void mostrarInventario();
void pantallamain();

#endif