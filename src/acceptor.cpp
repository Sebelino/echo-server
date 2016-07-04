/**
 * acceptor.cpp
 * Purpose: Provides the functionality needed for accepting connections from clients.
 *
 * @author Sebastian Olsson
 * @author Vic Hargrave
 */

#include <arpa/inet.h>
#include <string>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include "acceptor.hpp"

Acceptor::Acceptor(int port, std::string address)
    /**
     * Creates an acceptor instance with the given socket information. Sets listening to false.
     */
    : m_listen_descriptor(0), m_port(port), m_address(address), m_listening(false) {}

Acceptor::~Acceptor() {
    /**
     * Closes the socket descriptor if it is open, then frees the memory.
     */
    if (m_listen_descriptor > 0) {
        close(m_listen_descriptor);
    }
}

int Acceptor::start() {
    /**
     * Starts listening on the socket beloning to this instance.
     * Returns the return value for the listen(2) system call.
     */
    if (m_listening) {
        throw std::runtime_error("Already listening on this socket.");
    }

    m_listen_descriptor = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;

    std::memset(&address, 0, sizeof(address));
    address.sin_family = PF_INET;
    address.sin_port = htons(m_port);
    if (m_address.size() > 0) {
        inet_pton(PF_INET, m_address.c_str(), &(address.sin_addr));
    } else {
        address.sin_addr.s_addr = INADDR_ANY;
    }
    int optval = 1;
    setsockopt(m_listen_descriptor, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);
    int result = bind(m_listen_descriptor, (struct sockaddr*)&address, sizeof(address));
    if (result != 0) {
        throw std::runtime_error("bind() failed");
    }
    result = listen(m_listen_descriptor, 5);
    if (result != 0) {
        throw std::runtime_error("listen() failed");
    }
    m_listening = true;
    return result;
}

Stream Acceptor::accept() {
    /**
     * Returns a TCP stream for communicating with the client.
     */
    if (!m_listening) {
        throw std::runtime_error("Socket not listening");
    }
    struct sockaddr_in address;
    socklen_t len = sizeof(address);
    memset(&address, 0, sizeof(address));
    int sd = ::accept(m_listen_descriptor, (struct sockaddr*)&address, &len);
    if (sd < 0) {
        throw std::runtime_error("accept() failed");
    }
    Stream stream(sd, &address);
    return stream;
}
