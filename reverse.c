#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
int main(int argc, char *argv[]) {
    struct sockaddr_in serverAddr;
    int socketfd, port;
    char *serverIp;
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <IP> <Port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    serverIp = argv[1];
    port = atoi(argv[2]);
    if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    if (inet_pton(AF_INET, serverIp, &serverAddr.sin_addr) <= 0) {
        perror("inet_pton");
        close(socketfd);
        exit(EXIT_FAILURE);
    }
    if (connect(socketfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("connect");
        close(socketfd);
        exit(EXIT_FAILURE);
    }
    // Теперь можно использовать socketfd для общения с сервером
    // Например, отправить строку на сервер:
    char *message = "Привет, сервер!";
    if (send(socketfd, message, strlen(message), 0) < 0) {
        perror("send");
        close(socketfd);
        exit(EXIT_FAILURE);
    }
    // Здесь может быть код для чтения ответа сервера и т.д.
    // Закрываем сокет
    close(socketfd);
    return 0;
}
