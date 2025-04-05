#include <stdio.h>
#include <stdlib.h>
#include "guateque.h"
#include "guatequeDB.h"

Guateque g1;
Guateque g2;
Guateque *guateques;
int nguateques;

void prepararDatosPrueba(void){
    Evento e1 = {"Bizardunak", 20, "2025/04/04", "Bizardunak bueltan dira!", 0};
    Evento e2 = {"Chill Mafia", 30.5, "2025/03/28", "Agur eta Ohore, Chill Mafia badoa", 1};
    Evento e3 = {"HGA Japonia", 90, "2025/04/09", "HGA Japoniara Badoa!!",2};

    Evento *eventos;

    eventos = malloc(sizeof(Evento)*3);

    eventos[0] = e1;
    eventos[1] = e2;
    eventos[2] = e3;

    Evento e4 = {"Karate a Muerte en Torremolinos", 15, "2025/05/09", "Markelen urteak ospatzeko Karate a Muerte en Torremolinos pelikulearen proiekzinoa",4};
    Evento e5 = {"Austin Powers", 10, "2025/05/10", "Austin Powers-en trilogiaren proiekzinoa",5};

    Evento *eventos2;

    eventos2 = malloc(sizeof(Evento)*2);

    eventos2[0] = e4;
    eventos2[1] = e5;

    g1.nombre = "Begoñako Antzoki mundiala";
    g1.direccion = "Jose Maria Ugarteburu 5";
    g1.eventos = eventos;
    g1.neventos = 3;
    g1.id = 0;

    g2.nombre = "Inpernupe";
    g2.direccion = "San Roke kalea 4";
    g2.eventos = eventos2;
    g2.neventos = 2;
    g2.id = 1;


    guateques = malloc(sizeof(Guateque)*2);
    guateques[0] = g1;
    guateques[1] = g2;
    nguateques = 2;
}

void guardarBD(Guateque g){
    insertar_guateque(g);
    for (int i = 0; i < g.neventos; i++)
    {
        insertar_evento(g.eventos[i], g);
    }
    
}


int main(void){
    int opcion = 1;
    while(opcion != 0){
        printf("Bienvenido al gestor de guateques, elige que quieres hacer:\n");
        printf("    0) Salir");
        printf("    1) Consultar guateques y/o eventos");
        printf("    2) Resgistrar un nuevo guateque");
        printf("    3) Registrar un nuevo evento");
    
    }
    


    for (int i = 0; i < nguateques; i++)
    {
        Guateque g = guateques[i];
        guardarBD(g);

    }
    Guateque* guateques2 = get_guateques();
    //Evento* ebentos = get_eventos();
    
    for (int i = 0; i < nguateques; i++)
    {
       free(guateques[i].eventos);

    }
    free(guateques);

    for (int i = 0; i < nguatDB; i++)
    {
        free(guateques2[i].eventos);
    }
    
    free(guateques2);

    return 0;
}
