#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

#define START_COMMAND        128
#define STOP_COMMAND         129
#define RETURN_TO_BASE       130
#define TARGET_POINT         131
#define SET_SPEED            135
#define SET_DIRECTION        136
#define BATTERY              140
#define TIME                 141
#define MAP                  142
#define UNKNOWN_ERR          200
#define DATA_ERR             201
#define CONNECT_ERR          202
#define PING                 255

void parse_message(const char *message) {
    int code = atoi(message);
    
    switch (code) {
        case BATTERY:
            printf("Command executed: Battery Status Request\n");
            break;
        case TIME:
            printf("Command executed: Time Status Request\n");
            break;
        case MAP:
            printf("Command executed: Map Request\n");
            break;
        case START_COMMAND:
            printf("Command executed: START\n");
            break;
        case STOP_COMMAND:
            printf("Command executed: STOP\n");
            break;
        case RETURN_TO_BASE:
            printf("Command executed: RETURN TO BASE\n");
            break;
        case TARGET_POINT:
            printf("Command executed: TARGET POINT\n");
            break;
        case SET_SPEED:
            printf("Command executed: SET SPEED\n");
            break;
        case SET_DIRECTION:
            printf("Command executed: SET DIRECTION\n");
            break;
        case UNKNOWN_ERR:
            printf("Received unknown error.\n");
            break;
        default:
            printf("Received unknown command: %d\n", code);
            break;
    }
}

class ServerSocket {
public:
    void parseMessage(const char *message) {
        int code = atoi(message);
        
        switch (code) {
            case START_COMMAND:
                printf("Command executed: START\n");
                break;
            // Обработка других команд
            default:
                printf("Unknown command: %d\n", code);
                break;
        }
    }

    bool setupServer(int port) {
        int server_fd, new_socket;
        struct sockaddr_in address;
        int opt = 1;
        int addrlen = sizeof(address);
        
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
            perror("Socket failed");
            return false;
        }

        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
            perror("Setsockopt failed");
            return false;
        }
        
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);
        
        if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
            perror("Bind failed");
            return false;
        }

        if (listen(server_fd, 3) < 0) {
            perror("Listen failed");
            return false;
        }

        printf("Server is listening on port %d\n", port);

        while (1) {
            if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
                perror("Accept failed");
                continue;
            }

            char buffer[BUFFER_SIZE] = {0};
            read(new_socket, buffer, sizeof(buffer));
            printf("Received message: %s\n", buffer);
            parseMessage(buffer);
            close(new_socket);
        }

        return true;
    }
};

int main() {
    ServerSocket serverSocket;
    serverSocket.setupServer(8080);
    return 0;
}
