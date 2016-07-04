/**
 * client.cpp
 * Purpose: CLI application for connecting to a server socket and continuously send messages to it.
 *
 * @author Sebastian Olsson
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <ctime>
#include <future>
#include <vector>
#include <numeric>
#include <boost/format.hpp>
#include "connector.hpp"

double send_message(Stream* stream, std::string message) {
    /* Uses the TCP stream to send a message to the receiving socket.
     * Returns the round-trip time in milliseconds.
     */
    int len;
    char line[256];
    double microsecs;

    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
    stream->send(message.c_str(), message.size());
    std::cout << "Sent:     [" << message.c_str() << "]" << std::endl;
    len = stream->receive(line, sizeof(line));
    // usleep(3000000); /* Uncomment to simulate long RTT */
    std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();

    microsecs = std::chrono::duration_cast<std::chrono::microseconds>(end_time-start_time).count();
    double millisecs = microsecs/1000;

    line[len] = 0;
    std::cout << "Received: [" << line << "]" << ", RTT = " << millisecs << " ms" << std::endl;

    return millisecs;
}

double average(std::vector<double> values) {
    double sum = std::accumulate(values.begin(), values.end(), 0.0);
    double mean = sum/values.size();
    return mean;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cout << "usage: " << argv[0] << " <port> <ip>" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    Connector connector;
    Stream* stream;
    stream = connector.connect(argv[2], atoi(argv[1]));
    double rtt_sum = 0;
    uint64_t sent_bytes = 0;
    for (int i = 1;; i++) {
        std::string message = "Hello socket "+std::to_string(i);
        std::future<double> rttf = std::async(&send_message, stream, message);
        double rtt = rttf.get();
        rtt_sum += rtt;
        sent_bytes += message.size();
        usleep(1000000);
        std::cout << "Average RTT = " << rtt_sum/i << " ms";
        std::cout << ", throughput rate = " << 1000*8*sent_bytes/rtt_sum << " bps" << std::endl;
    }
    return 0;
}
