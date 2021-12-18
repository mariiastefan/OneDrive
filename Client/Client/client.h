#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

class Client_socket {
    std::fstream file;

    int PORT;

    int general_socket_descriptor;

    struct sockaddr_in address;
    int address_length;

public:
    Client_socket() {
        create_socket();
        PORT = 8050;

        address.sin_family = AF_INET;
        address.sin_port = htons(PORT);
        address_length = sizeof(address);
        if (inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) <= 0) {
            std::cout << "[ERROR] : Invalid address\n";
        }

        create_connection();

        file.open("client_text.txt", std::ios::out | std::ios::trunc | std::ios::binary);
        if (file.is_open()) {
            std::cout << "[LOG] : File Creted.\n";
        }
        else {
            std::cout << "[ERROR] : File creation failed, Exititng.\n";
            exit(EXIT_FAILURE);
        }
    }

    void create_socket() {
        if ((general_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            perror("[ERROR] : Socket failed.\n");
            exit(EXIT_FAILURE);
        }
        std::cout << "[LOG] : Socket Created Successfully.\n";
    }

    void create_connection() {
        if (connect(general_socket_descriptor, (struct sockaddr*)&address, sizeof(address)) < 0) {
            perror("[ERROR] : connection attempt failed.\n");
            exit(EXIT_FAILURE);
        }
        std::cout << "[LOG] : Connection Successfull.\n";
    }

    void receive_file() {
        char buffer[1024] = {};
        int valread = recv(general_socket_descriptor, buffer, 1024, 0);
        std::cout << "[LOG] : Data received " << valread << " bytes\n";
        std::cout << "[LOG] : Saving data to file.\n";

        file << buffer;
        std::cout << "[LOG] : File Saved.\n";
    }
};

