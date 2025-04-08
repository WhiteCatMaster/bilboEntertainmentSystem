#include <stdio.h>
#include "guateque.h"
#include "guatequeDB.h"

void imprimirEventos(Guateque g){
    printf("Nombre: %s, Direccion: %s\n", g.nombre, g.direccion);
    printf("Eventos disponibles: %d\n",g.neventos);
    printf("    0)Exit\n");
    if (g.neventos==0){
        printf("\n**********************************************************\n");
        printf("No existen eventos para el guateque %s\n",g.nombre);
        printf("**********************************************************\n");
    }
    else
    {
        printf("\n**********************************************************\n");
        printf("Se han encontrado estos eventos para el guateque %s:\n",g.nombre);
        for (int i = 0; i < g.neventos; i++)
        {
            Evento e = g.eventos[i];
            printf("    %d)%s, %s, %f Eur\n", i+1, e.nombre, e.fecha, e.precio);
            printf("        %s\n\n", e.descripcion);
        }
        printf("Fin de lista de eventos.\n");
        printf("**********************************************************\n");
    }
}

void imprimirGuateques(Guateque *g){
    printf("\n**********************************************************\n");
    printf("Seleciona un guateque: \n");
    printf("    0)Exit\n");
    //int n_guateque = sizeof (g[0]) / sizeof(g);
    //printf("guateque:imprimirGuateque:INFO sizeof (g) = %ld\n",sizeof (g));
    //printf("guateque:imprimirGuateque:INFO sizeof (g[0]) = %ld\n",sizeof (g[0]));
    //printf("guateque:imprimirGuateque:INFO n_guateque = %d\n",n_guateque);
    for (int i = 0; i < contar_guateques(); i++)
    //for (int i = 0; i < n_guateque; i++)
    {
        Guateque guateque = g[i];
        printf("    %d)%s\n", i+1, guateque.nombre);
    }
    printf("**********************************************************\n");
}

