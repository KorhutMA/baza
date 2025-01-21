#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PASSWORD "orangepi"

void execute_command(const char *command) {
    int result = system(command);
    if (result == -1) {
        perror("Ошибка выполнения команды");
    }
}

int main() {
    char input[100];

    printf("Введите пароль: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    if (strcmp(input, PASSWORD) != 0) {
        printf("Неверный пароль!\n");
        return 1;
    }

    const char *backup_command = "sudo cp /etc/NetworkManager/NetworkManager.conf /etc/NetworkManager/NetworkManager.conf.bak";
    const char *edit_command = "echo -e \"[main]\nplugins=\n\n[ifupdown]\nmanaged=false\" | sudo tee /etc/NetworkManager/NetworkManager.conf > /dev/null";
    const char *restart_command = "sudo systemctl restart NetworkManager";
    const char *reboot_command = "sudo reboot";

    execute_command(backup_command);
    execute_command(edit_command);
    execute_command(restart_command);
    execute_command(reboot_command);

    return 0;
}
