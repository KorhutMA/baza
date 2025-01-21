#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

class WiFiConfig {
private:
    std::string ssid;
    std::string password;

public:
    bool readNetworkCredentials() {
        std::ifstream credFile("/home/orangepi/serverclient/network_credentials.txt");
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

    if (config.readNetworkCredentials()) {
        std::string ssid = config.getSSID();
        std::string password = config.getPassword();
        
        std::string connect_cmd = "nmcli dev wifi connect '" + ssid + "' password '" + password + "'";
        if (system(connect_cmd.c_str()) != 0) {
            std::cerr << "Failed to connect to WiFi" << std::endl;
        } else {
            std::cout << "Connected to " << ssid << " successfully." << std::endl;
        }
    }

    return 0;
}
