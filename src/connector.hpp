/**
 * connector.hpp
 * Purpose: Provides the functionality needed for establishing a connection to a server socket.
 *
 * @author Sebastian Olsson
 * @author Vic Hargrave
 */

#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "stream.hpp"

class Connector {
public:
    Stream* connect(std::string ip, int port);
};

#endif /* CONNECTOR_H */
