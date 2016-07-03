TESTFLAGS = -I/usr/include/ -L/usr/lib/ -lgtest -lpthread

all: bin/server bin/client

build/server.o: build src/server.cpp
	g++ src/server.cpp -c -o $@

build/client.o: build src/client.cpp
	g++ src/client.cpp -c -o $@

build/test_integration.o: build test/test_integration.cpp
	g++ test/test_integration.cpp -c -o $@

build:
	mkdir -p build/

bin/server: bin build/server.o
	g++ build/server.o -o $@

bin/client: bin build/client.o

bin/test_integration: bin build/test_integration.o build/server.o
	g++ $(TESTFLAGS) build/test_integration.o build/server.o -o $@

bin:
	mkdir -p bin/

clean:
	rm -rf build/
	rm -rf bin/

.PHONY: clean
