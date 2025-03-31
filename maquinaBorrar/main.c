#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include "MaquinaExpendedora.h"

typedef struct {
    char* nombre;
    float precio;
} Producto;

typedef struct {
    Producto *productos;
    int cantidades;
    int tamanyo;
    int pos;
} Linea;

void imprimirProducto(Producto *producto) {
printf("%s: %.2f euros\n", producto ->nombre, producto ->precio);
}

int main(int argc, char const *argv[])
{
    Producto producto = {"Chocoboms", 1.8};
    imprimirProducto(&producto);

    return 0;
}