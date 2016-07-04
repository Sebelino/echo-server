TESTFLAGS = -I/usr/include/ -L/usr/lib/ -lgtest -lpthread

all: bin/server bin/client

build/%.o: src/%.cpp
	mkdir -p build
	g++ $^ -c -o $@

bin/server: build/server.o build/stream.o build/acceptor.o
	mkdir -p bin
	g++ $^ -o $@

bin/client: build/client.o build/stream.o build/connector.o
	mkdir -p bin
	g++ -lpthread $^ -o $@

bin/test_integration: bin build/test_integration.o build/server.o
	g++ $(TESTFLAGS) build/test_integration.o build/server.o -o $@

clean:
	rm -rf build/
	rm -rf bin/

.PHONY: clean
