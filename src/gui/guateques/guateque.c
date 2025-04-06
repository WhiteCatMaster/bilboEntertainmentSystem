#include <stdio.h>
#include "guateque.h"
#include "guatequeDB.h"

void imprimirEventos(Guateque g){
    printf("Nombre: %s, Direccion: %s\n", g.nombre, g.direccion);
    printf("Eventos:\n");
    printf("    0)Exit\n");
    printf("%d",g.neventos);
    for (int i = 0; i < g.neventos; i++)
    {
        Evento e = g.eventos[i];
        printf("    %d)%s, %s, %f Eur\n", i+1, e.nombre, e.fecha, e.precio);
        printf("        %s\n\n", e.descripcion);
    }
}

void imprimirGuateques(Guateque *g){
    printf("Seleciona un guateque: \n");
    printf("    0)Exit\n");
    for (int i = 0; i < contar_guateques(); i++)
    {
        Guateque guateque = g[i];
        printf("    %d)%s\n", i+1, guateque.nombre);
    }
    
}

