#include "main.h"
#include "../../../BBDD/cineDB.h"
#include "../../../main/mainMenu.h"

void ejecutar_programa(const char *comando) {
    // Usamos popen para ejecutar el comando y obtener su salida estándar
    printf("Ejecutando el comando: %s\n", comando);
    FILE *fp = popen(comando, "r");

    if (fp == NULL) {
        perror("Error al ejecutar el comando");
        return;
    }

    // Leemos la salida del programa ejecutado
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer); // Imprimimos en la terminal lo que el otro programa imprima
    }

    // Cerramos el pipe
    fclose(fp);
}

int mainCine() {
    pyAlhondiga();
    borrarbdLibro();
  	// system("cd ..\\mano");
    // ejecutar_programa("..\\mano\\controlxdDedos.exe");

    clear_screen();  // Clear the screen
    char c;
    while (c != '0'){
        leerTcine();
        consultorAPI();
        printf("\n");
        printf("BIENVENIDO AL CINE!\n");
        printf("===================================\n ");
        printf("0) Comprar entradas\n");
        printf("1) Añadir critican\n");
        printf("2) Salir\n");
        c = getchar();
        if(c == '0'){
          	clear_screen();
            comprarEntradas();
        }else if (c == '1'){
            clear_screen();
            ensenar_criticas();
        }else if (c == '2'){
            printf("Saliendo del cine...\n");
            printf("\n");
            selector();

        }else {

            clear_screen();
        }
    }
    system("PAUSE");  // Pause the program
    return 0;
}
