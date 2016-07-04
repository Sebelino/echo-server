/**
 * stream.hpp
 * Purpose: Provides functionality needed for sending and receiving messages between established
 * sockets.
 *
 * @author Sebastian Olsson
 * @author Vic Hargrave
 */

#ifndef STREAM_H
#define STREAM_H

#include <string>
#include <unistd.h>

class Stream {
    int m_socket_descriptor;
    std::string m_peer_ip;
    int m_peer_port;

public:
    friend class Acceptor;
    friend class Connector;
    ~Stream();
    ssize_t receive(char* buffer, size_t len, int timeout=0);
    ssize_t send(const char* buffer, size_t len);
    std::string peer_ip();
    int peer_port();
    bool wait_for_read_event(int timeout);

private:
    Stream(int socket_descriptor, struct sockaddr_in* address);
};

#endif /* STREAM_H */
