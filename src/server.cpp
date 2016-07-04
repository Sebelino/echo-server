/**
 * server.cpp
 * Purpose: CLI application for accepting connections from clients and echoing their messages.
 *
 * @author Sebastian Olsson
 */

#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <string>
#include <sstream>
#include "acceptor.hpp"

void run_server(int port, std::string ip) {
    /**
     * Establishes and starts listening on a server socket on the specified port and IP address.
     */
    Acceptor acceptor(port, ip);
    std::cout << "Initialized TCP acceptor on " << ip << ":" << port << std::endl;
    if (acceptor.start() == 0) {
        std::cout << "Started TCP acceptor..." << std::endl;
        while (true) {
            Stream stream = acceptor.accept();  // Blocking call
            ssize_t len;
            char line[256]; // Enough? std::string?
            while ((len = stream.receive(line, sizeof(line))) > 0) {
                line[len] = '\0';
                std::stringstream response;
                response << "[" << line << "] from " << stream.peer_ip();
                response << ":" << stream.peer_port();
                std::cout << "Received: " << response.str() << std::endl;
                stream.send(line, len);
            }
        }
    }
}

void validate_arguments(int port, std::string ip) {
    /**
     * Throws an exception if the socket is incorrectly specified.
     */
    if (port < 0 && port > 65535) {
        throw std::invalid_argument("Port number is not within [0, 65535] range");
    }
}

int main(int argc, char* argv[]) {
    /**
     * Supplies the CLI functionality for setting up a server socket.
     */
    if (argc != 3) {
        std::cout << "usage: " << argv[0] << " <port> <ip>" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    int port_number = atoi(argv[1]);
    std::string ip_address = argv[2];
    validate_arguments(port_number, ip_address);
    run_server(port_number, ip_address);
    return 0;
}
