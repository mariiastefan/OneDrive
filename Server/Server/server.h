#include<iostream>
#include<fstream>
#include <stdlib.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

class Server_socket {
    std::fstream file;

    int PORT;

    int general_socket_descriptor;
    int new_socket_descriptor;

    struct sockaddr_in address;
    int address_length;

public:
    Server_socket() {
        create_socket();
        PORT = 8050;

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(PORT);
        address_length = sizeof(address);

        bind_socket();
        set_listen_set();
        accept_connection();

        file.open("server_text.txt", std::ios::in | std::ios::binary);
        if (file.is_open()) {
            std::cout << "[LOG] : File is ready to Transmit.\n";
        }
        else {
            std::cout << "[ERROR] : File loading failed, Exititng.\n";
            exit(EXIT_FAILURE);
        }
    }

    void create_socket() {
        if ((general_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
            perror("[ERROR] : Socket failed");
            exit(EXIT_FAILURE);
        }
        std::cout << "[LOG] : Socket Created Successfully.\n";
    }

    void bind_socket() {
        if (bind(general_socket_descriptor, (struct sockaddr*)&address, sizeof(address)) < 0) {
            perror("[ERROR] : Bind failed");
            exit(EXIT_FAILURE);
        }
        std::cout << "[LOG] : Bind Successful.\n";
    }

    void set_listen_set() {
        if (listen(general_socket_descriptor, 3) < 0) {
            perror("[ERROR] : Listen");
            exit(EXIT_FAILURE);
        }
        std::cout << "[LOG] : Socket in Listen State (Max Connection Queue: 3)\n";
    }

    void accept_connection() {
        if ((new_socket_descriptor = accept(general_socket_descriptor, (struct sockaddr*)&address, (socklen_t*)&address_length)) < 0) {
            perror("[ERROR] : Accept");
            exit(EXIT_FAILURE);
        }
        std::cout << "[LOG] : Connected to Client.\n";
    }

    void transmit_file() {
        std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        std::cout << "[LOG] : Transmission Data Size " << contents.length() << " Bytes.\n";

        std::cout << "[LOG] : Sending...\n";

        int bytes_sent = send(new_socket_descriptor, contents.c_str(), contents.length(), 0);
        std::cout << "[LOG] : Transmitted Data Size " << bytes_sent << " Bytes.\n";

        std::cout << "[LOG] : File Transfer Complete.\n";
    }
};

