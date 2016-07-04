/**
 * acceptor.hpp
 * Purpose: Provides the functionality needed for accepting connections from clients.
 *
 * @author Sebastian Olsson
 * @author Vic Hargrave
 */

#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include <string>
#include <netinet/in.h>
#include "stream.hpp"

class Acceptor {
    int m_listen_descriptor;
    int m_port;
    std::string m_address;
    bool m_listening;

public:
    Acceptor(int port, std::string address="");
    ~Acceptor();
    int start();
    Stream accept();

private:
    Acceptor() {}
};

#endif /* ACCEPTOR_H */
