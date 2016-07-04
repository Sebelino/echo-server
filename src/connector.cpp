/**
 * connector.cpp
 * Purpose: Provides the functionality needed for establishing a connection to a server socket.
 *
 * @author Sebastian Olsson
 * @author Vic Hargrave
 */

#include <netinet/in.h>
#include <string>
#include <cstring>
#include <stdexcept>
#include "connector.hpp"

Stream* Connector::connect(std::string ip, int port) {
    /**
     * Factory method for creating a TCP stream from the specified IP address and port.
     */
    struct sockaddr_in address;

    std::memset (&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);

    // Create and connect the socket, bail if we fail in either case
    int sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0) {
        throw std::runtime_error("socket() failed");
    }
    if (::connect(sd, (struct sockaddr*)&address, sizeof(address)) != 0) {
        close(sd);
        throw std::runtime_error("connect() failed");
    }
    Stream* stream = new Stream(sd, &address);
    return stream;
}
