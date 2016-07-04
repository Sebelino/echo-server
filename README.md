# Echo server
Simple C++ server application that echoes all incoming TCP messages back to the client,
based on the article
[TCP/IP Network Design Patterns in C++](http://vichargrave.com/network-programming-design-patterns-in-c/).
Also includes a client application which sends a short message at regular time intervals.
The applications are assumed to be built and executed on Linux.

## Installation
To generate the client and server executables below `bin/`:
```
$ make
```

## bin/server
The server application accepts a port number and an IP address which together constitute the server
socket to accept connections from:
```
usage: ./bin/server <port> <ip>
```
Example:
```
$ sudo ./bin/server 8000 127.0.0.1
```
To use well-known ports (i.e. ports in the range 0-1023), run the command as superuser:
```
$ sudo ./bin/server 80 127.0.0.1
```

## bin/client
The server application accepts a port number and an IP address which together constitute the server
socket to connect to:
```
usage: ./bin/client <port> <ip>
```
Example:
```
$ ./bin/client 8000 127.0.0.1
```
To use well-known ports (i.e. ports in the range 0-1023), run the command as superuser:
```
$ sudo ./bin/server 80 127.0.0.1
```

## Example
Output from `bin/server`:
```
$ ./bin/server 8000 127.0.0.1
Initialized TCP acceptor on 127.0.0.1:8000
Started TCP acceptor...
Received: [Hello socket 1] from 127.0.0.1:46290
Received: [Hello socket 2] from 127.0.0.1:46290
Received: [Hello socket 3] from 127.0.0.1:46290
Received: [Hello socket 4] from 127.0.0.1:46290
Received: [Hello socket 5] from 127.0.0.1:46290
Received: [Hello socket 6] from 127.0.0.1:46290
```
Output from `bin/client`:
```
$ ./bin/client 8000 127.0.0.1 
Sent:     [Hello socket 1]
Received: [Hello socket 1], RTT = 0.474 ms
Average RTT = 0.474 ms, throughput rate = 236287 bps
Sent:     [Hello socket 2]
Received: [Hello socket 2], RTT = 0.402 ms
Average RTT = 0.438 ms, throughput rate = 255708 bps
Sent:     [Hello socket 3]
Received: [Hello socket 3], RTT = 0.357 ms
Average RTT = 0.411 ms, throughput rate = 272506 bps
Sent:     [Hello socket 4]
Received: [Hello socket 4], RTT = 0.394 ms
Average RTT = 0.40675 ms, throughput rate = 275353 bps
Sent:     [Hello socket 5]
Received: [Hello socket 5], RTT = 0.175 ms
Average RTT = 0.3604 ms, throughput rate = 310766 bps
Sent:     [Hello socket 6]
Received: [Hello socket 6], RTT = 0.36 ms
```
