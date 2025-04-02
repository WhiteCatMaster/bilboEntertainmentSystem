#include <stdio.h>
#include <stdlib.h>
#include "guateque.h"

Guateque g1;
Guateque g2;
Guateque *guateques;
int nguateques;

void prepararDatosPrueba(void){
    Evento e1 = {"Bizardunak", 20, "2025/04/04", "Bizardunak bueltan dira!"};
    Evento e2 = {"Chill Mafia", 30.5, "2025/03/28", "Agur eta Ohore, Chill Mafia badoa"};
    Evento e3 = {"HGA Japonia", 90, "2025/04/09", "HGA Japoniara Badoa!!"};

    Evento *eventos;

    eventos = malloc(sizeof(Evento)*3);

    eventos[0] = e1;
    eventos[1] = e2;
    eventos[2] = e3;

    Evento e4 = {"Karate a Muerte en Torremolinos", 15, "2025/05/09", "Markelen urteak ospatzeko Karate a Muerte en Torremolinos pelikulearen proiekzinoa"};
    Evento e5 = {"Austin Powers", 10, "2025/05/10", "Austin Powers-en trilogiaren proiekzinoa"};

    Evento *eventos2;

    eventos2 = malloc(sizeof(Evento)*2);

    eventos2[0] = e4;
    eventos2[1] = e5;

    g1.nombre = "Begoñako Antzoki mundiala";
    g1.direccion = "Jose Maria Ugarteburu 5";
    g1.eventos = eventos;
    g1.neventos = 3;

    g2.nombre = "Inpernupe";
    g2.direccion = "San Roke kalea 4";
    g2.eventos = eventos2;
    g2.neventos = 2;


    guateques = malloc(sizeof(Guateque)*2);
    guateques[0] = g1;
    guateques[1] = g2;
    nguateques = 2;
}


int main(void){
    prepararDatosPrueba();
    int opcion = 1;
    while (opcion != 0)
    {
        imprimirGuateques(guateques, 2);
        scanf("%d", &opcion);
        if(opcion <= nguateques && opcion > 0){
            Guateque guateque = guateques[opcion-1];
            imprimirEventos(guateque);
            scanf("%d", &opcion);
            if(opcion <= guateque.neventos && opcion > 0){
                printf("Guardado el evento %s\n", guateque.eventos[opcion-1].nombre); //No lo he guardado jeje...
            }

            break;
        }else if(opcion != 0){
            printf("Error, no existe ese guateque\n");
        }
    }
    
    for (int i = 0; i < nguateques; i++)
    {
       free(guateques[i].eventos);
    }
    
    free(guateques);
    return 0;
}