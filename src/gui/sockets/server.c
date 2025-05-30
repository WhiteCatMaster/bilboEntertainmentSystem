#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "../../../src/BBDD/cineDB.h"


#define PORT 5000
#define MAX_BUFFER 1024

int serverMain() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[MAX_BUFFER] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Fallo en socket");
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Abrimos un socket en la dirección y puerto especificados
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Fallo en bind");
        return 1;
    }

    // Empezamos a escuchar las conexiones
    if (listen(server_fd, 3) < 0) {
        perror("Fallo en listen");
        return 1;
    }

    printf("Escuchando en el puerto %d...\n", PORT);

    buffer[0] = '\0';
    // Si el mensaje no es S seguimos escuchando
    while (1) {

        // Aceptamos conexión entrante
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Fallo en accept");
            return 1;
        }
        // Leemos el mensaje del socket
        read(new_socket, buffer, MAX_BUFFER);
        char numero = buffer[0];
        int num = numero -'0';
        char response = '0';
        switch (num) {
            case 1:
                borrarbdPelicula();               
                response = '1';
                break;
            case 2:
                borrarbdTarjeta();
                response = '2';
                break;
            case 3:
                borrarbdInventario();
                response = '3';
                break;
            case 4:
                borrarbdPelicula();
                response = '4';
                break;
            case 5:
                borrarbdCritica();
                response = '5';
                break;
            default:
                printf("\nOpcion invalida. Intente de nuevo.\n");
                break;
        }

        // Enviarmos respuesta al cliente
        char respuesta[2];
        respuesta[0] = response;
        respuesta[1] = '\0';
        send(new_socket, respuesta, sizeof(response), 0);
        

        // Limpiamos el buffer
        memset(buffer, 0, MAX_BUFFER);
    }

    // Cerramos la conexión
    close(new_socket);
    close(server_fd);

    return 0;
}