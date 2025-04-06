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
        insertar_evento(g.eventos[i]);
    }
    
}


int main(void){
    Guateque* guateque;
    int opcion = 1;
    while(opcion != 0){
        guateque = get_guateques();
        printf("Bienvenido al gestor de guateques, elige que quieres hacer:\n");
        printf("    0) Salir\n");
        printf("    1) Consultar guateques y/o eventos\n");
        printf("    2) Resgistrar un nuevo guateque\n");
        printf("    3) Registrar un nuevo evento\n");
        scanf("%d", &opcion);
        switch (opcion){
            case 0:
                break;
            case 1:
                imprimirGuateques(guateque, contar_guateques());
                scanf("%d", &opcion);
                imprimirEventos(guateque[opcion-1]);
                break;
            case 2:
                Guateque nuevoguateque;
                printf("Introduce el nombre del guateque:\n");
                nuevoguateque.nombre = malloc(sizeof(char)*100);
                scanf("%s", nuevoguateque.nombre);
                printf("Introduce la direccion:\n");
                nuevoguateque.direccion = malloc(sizeof(char)*100);
                scanf("%s", nuevoguateque.direccion);
                nuevoguateque.id = obtenerIdGuateque();
                insertar_guateque(nuevoguateque);
                printf("Se ha guardado el guateque:\n");
                free(nuevoguateque.nombre);
                free(nuevoguateque.direccion);
                break;
            case 3:
                Evento evento;
                printf("Introduce el nombre del evento:\n");
                evento.nombre = malloc(sizeof(char)*100);
                scanf("%s", evento.nombre);
                printf("Introduce la fecha AAAA/MM/DD:\n");
                evento.fecha = malloc(sizeof(char)*100);
                scanf("%s", evento.fecha);
                printf("Introduce el precio del evento:\n");
                scanf("%f", &evento.precio);
                printf("Introduce una breve descripcion:\n");
                evento.descripcion = malloc(sizeof(char)*100);
                scanf("%s", evento.descripcion);
                evento.id = obtenerIdEvento();
                printf("En cual de estos guateques va a tener lugar?\n");
                imprimirGuateques(guateque, contar_guateques());
                int id;
                scanf("%d", &id);
                evento.idg = guateque[id-1].id;
                insertar_evento(evento);
                printf("%d", obtenerIdEvento());
                printf("Se ha guardado el evento:\n");
                free(evento.nombre);
                free(evento.fecha);
                free(evento.descripcion);
                break;
            default:
                printf("No es una opcion valida");
        }
    }
    
    
    for (int i = 0; i < nguateques; i++)
    {
        for (int j = 0; i < contar_guateques(); i++)
        {
            free(guateque[i].eventos[j].nombre);
            free(guateque[i].eventos[j].descripcion);
            free(guateque[i].eventos[j].fecha);
        }
        
       free(guateque[i].eventos);
       free(guateque[i].nombre);
       free(guateque[i].direccion);

    }
    free(guateque);

    return 0;
}
