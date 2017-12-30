CC=g++
RM=rm
CFLAGS=-I.
LDFLAGS=-lsfml-system -lsfml-window -lsfml-graphics -lsfml-network

SERVER = server
SERVER_HEADERS = NetworkProtocol.hpp GameServer.hpp
SERVER_SOURCES = server.cpp GameServer.cpp
SERVER_OBJECTS = $(subst .cpp,.o,$(SERVER_SOURCES))

all: $(SERVER)

$(SERVER): $(SERVER_OBJECTS)
	$(CC) -o $(SERVER) $(SERVER_OBJECTS) $(CFLAGS) $(LDFLAGS)

$(SERVER_OBJECTS): $(SERVER_SOURCES) $(SERVER_HEADERS)
	$(CC) -c $(SERVER_SOURCES) $(CFLAGS) $(LDFLAGS)

clean:
	$(RM) $(SERVER_OBJECTS)
	$(RM) $(SERVER)

.PHONY: clean all
