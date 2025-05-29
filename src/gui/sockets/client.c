#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "client.h"

#define PORT 5000
#define MAX_BUFFER 1024

int enviarMensaje(char c){

    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[MAX_BUFFER] = {0};

    // Crear socket de archivo descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Fallo en la creación del socket \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convertir la dirección IPv4 e IPv6 de texto a formato binario
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nDirección inválida / Dirección no soportada \n");
        return -1;
    }

    // Nos conectamos al servidor
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nFalló la conexión \n");
        return -1;
    }

     // Enviamos un mensaje al servidor
    send(sock, c, sizeof(c), 0);
    printf("Mensaje enviado: %s\n", argv[1]);

    // Leemos la respuesta del servidor
    read(sock, buffer, MAX_BUFFER);
    printf("Respuesta del servidor: %s\n", buffer);
    if(buffer == '0'){
        printf("Comando ejecutado correctamente");
        return 0;
    }else{
        printf("Error en el envio y/o ejecucion del comando");
        return -1;
    }

    close(sock);

    
}
