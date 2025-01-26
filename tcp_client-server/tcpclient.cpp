#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

class ClientSocket {
public:
    bool sendCommand(const char* serverIP, int port, const char* command) {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            printf("Socket creation failed\n");
            return false;
        }

        struct sockaddr_in serv_addr;
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(port);

        if (inet_pton(AF_INET, serverIP, &serv_addr.sin_addr) <= 0) {
            printf("Invalid address\n");
            close(sock);
            return false;
        }

        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            printf("Connection Failed\n");
            close(sock);
            return false;
        }

        send(sock, command, strlen(command), 0);
        printf("Command sent: %s\n", command);
    
        close(sock);
        return true;
    }
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <Server_IP> <Command>\n", argv[0]);
        return -1;
    }

    const char* serverIP = argv[1];
    const char* command = argv[2];
    int port = 8080;

    ClientSocket clientSocket;

    if (!clientSocket.sendCommand(serverIP, port, command)) {
        printf("Failed to send command to %s:%d\n", serverIP, port);
        return -1;
    }

    return 0;
}
