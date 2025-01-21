#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // Для использования system()

class WiFiConfig {
private:
    std::string ssid;
    std::string password;

public:
    void saveNetworkCredentials(const std::string& networkSSID, const std::string& networkPassword) {
        std::ofstream credFile("/home/korhutma/Documents/network_credentials.txt");
        if (!credFile) {
            std::cerr << "Error opening file for writing" << std::endl;
            return;
        }
        credFile << networkSSID << std::endl;
        credFile << networkPassword << std::endl;
        credFile.close();
        
        std::cout << "Saved Credentials: " << std::endl;
        std::cout << "SSID: " << networkSSID << std::endl;
        std::cout << "Password: " << networkPassword << std::endl;
        std::cout << "Credentials saved successfully" << std::endl;
    }

    bool readNetworkCredentials() {
        std::ifstream credFile("/home/korhutma/Documents/network_credentials.txt");
        if (!credFile.is_open()) {
            std::cout << "Unable to open credentials file" << std::endl;
            return false;
        }

        if (!std::getline(credFile, ssid)) {
            std::cerr << "Error reading SSID from file" << std::endl;
            return false;
        }
        if (!std::getline(credFile, password)) {
            std::cerr << "Error reading Password from file" << std::endl;
            return false;
        }
        
        credFile.close();
        return true;
    }

    std::string getSSID() const { return ssid; }
    std::string getPassword() const { return password; }
};

int main() {
    WiFiConfig config;
    std::string ssid;
    std::string password;

    std::cout << "Введите имя сети (SSID): ";
    std::getline(std::cin, ssid);
    std::cout << "Введите пароль сети: ";
    std::getline(std::cin, password);
    
    config.saveNetworkCredentials(ssid, password);

    if (config.readNetworkCredentials()) {
        std::cout << "Прочитанная SSID: " << config.getSSID() << std::endl;
        std::cout << "Прочитанный пароль: " << config.getPassword() << std::endl;
    }

    std::string command = "scp /home/korhutma/Documents/network_credentials.txt orangepi@192.168.1.1:/home/orangepi/serverclient";
    int result = system(command.c_str());
    if (result == 0) {
        std::cout << "Файл успешно скопирован на удалённый сервер." << std::endl;
    } else {
        std::cerr << "Ошибка при копировании файла на удалённый сервер." << std::endl;
    }

    return 0;
}
