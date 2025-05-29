#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 5000
#define MAX_BUFFER 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[MAX_BUFFER] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Fallo en socket");
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Abrimos un socket en la dirección y puerto especificados
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Fallo en bind");
        return -1;
    }

    // Empezamos a escuchar las conexiones
    if (listen(server_fd, 3) < 0) {
        perror("Fallo en listen");
        return -1;
    }

    printf("Escuchando en el puerto %d...\n", PORT);

    buffer[0] = '\0';
    // Si el mensaje no es S seguimos escuchando
    while (strcmp(buffer, 'S') != 0) {

        // Aceptamos conexión entrante
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Fallo en accept");
            return -1;
        }
        // Leemos el mensaje del socket
        read(new_socket, buffer, MAX_BUFFER);
        char response = '0';
        switch (buffer) {
            case '1':
                //void borrarbdLibro();
                //Comunicarse con la funcion que esta en cineDB.c, si se borra correctamente devuelve un 0, si llega un 0
                //poner algun mensaje de tarjeta borrada correctamente.
                break;
            case '2':
                //borrarbdTarjeta();
                break;
            case '3':
                //borrarbdInventario();
                break;
            case '4':
                //borrarbdPelicula();
                break;
            case '5':
                //borrarbdCritica();
                break;
            case 'S':
            case 's':
                printf("Saliendo del programa");
                return 0;
            default:
                printf("\nOpcion invalida. Intente de nuevo.\n");
                break;
                response = '1';
        }

        // Enviarmos respuesta al cliente
        send(new_socket, response, strlen(response), 0);
        
        printf("Mensaje enviado al cliente\n");

        // Limpiamos el buffer
        memset(buffer, 0, MAX_BUFFER);
    }

    // Cerramos la conexión
    close(new_socket);
    close(server_fd);

    return 0;
}