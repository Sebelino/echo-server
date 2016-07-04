/**
 * stream.cpp
 * Purpose: Provides functionality needed for sending and receiving messages between established
 * sockets.
 *
 * @author Sebastian Olsson
 * @author Vic Hargrave
 */

#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <ctime>
#include "stream.hpp"

Stream::Stream(int socket_descriptor, struct sockaddr_in* address)
    : m_socket_descriptor(socket_descriptor) {
    char ip[50];
    inet_ntop(PF_INET, (struct in_addr*) & (address->sin_addr.s_addr), ip, sizeof(ip)-1);
    m_peer_ip = ip;
    m_peer_port = ntohs(address->sin_port);
}

Stream::~Stream() {
    close(m_socket_descriptor);
}

std::string Stream::peer_ip() {
    return m_peer_ip;
}

int Stream::peer_port() {
    return m_peer_port;
}

ssize_t Stream::receive(char* buffer, size_t len, int timeout) {
    if (timeout <= 0 || wait_for_read_event(timeout)) {
        return read(m_socket_descriptor, buffer, len);
    }
    return -1; // Connection timed out
}

ssize_t Stream::send(const char* buffer, size_t len) {
    ssize_t nbytes = write(m_socket_descriptor, buffer, len);
    return nbytes;
}

bool Stream::wait_for_read_event(int timeout) {
    fd_set sdset;
    struct timeval tv;
    tv.tv_sec = timeout;
    tv.tv_usec = 0;
    FD_ZERO(&sdset);
    FD_SET(m_socket_descriptor, &sdset);
    if (select(m_socket_descriptor+1, &sdset, NULL, NULL, &tv) > 0) {
        return true;
    }
    return false;
}
