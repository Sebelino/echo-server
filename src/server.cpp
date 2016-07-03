/* Copyright 2016 Sebastian Olsson */
// Server application placeholder

#include <iostream>
#include <stdexcept>

double square_root(const double x) {
    if (x < 0) {
        throw std::invalid_argument("Received negative value.");
    }
    double lower = 0;
    double upper = x;
    double mean = lower;
    int iterations = 100;
    for (int i = 0; i < iterations; i++) {
        mean = (lower+upper)/2;
        if (mean*mean == x) {
            return mean;
        } else if (mean*mean > x) {
            upper = mean;
        } else {
            lower = mean;
        }
    }
    throw std::invalid_argument("Did not converge.");
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "usage: ./server <port> <ip>" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    return 0;
}
