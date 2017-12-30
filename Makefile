CC=g++
RM=rm
CFLAGS=-I.
LDFLAGS=-lsfml-system -lsfml-window -lsfml-graphics -lsfml-network

SERVER = server
SERVER_HEADERS = NetworkProtocol.hpp GameServer.hpp
SERVER_SOURCES = server.cpp GameServer.cpp
SERVER_OBJECTS = $(subst .cpp,.o,$(SERVER_SOURCES))

CLIENT = client
CLIENT_HEADERS = NetworkProtocol.hpp GameClient.hpp
CLIENT_SOURCES = client.cpp GameClient.cpp
CLIENT_OBJECTS = $(subst .cpp,.o,$(CLIENT_SOURCES))

all: $(SERVER) $(CLIENT)

$(SERVER): $(SERVER_OBJECTS)
	$(CC) -o $(SERVER) $(SERVER_OBJECTS) $(CFLAGS) $(LDFLAGS)

$(SERVER_OBJECTS): $(SERVER_SOURCES) $(SERVER_HEADERS)
	$(CC) -c $(SERVER_SOURCES) $(CFLAGS) $(LDFLAGS)

$(CLIENT): $(CLIENT_OBJECTS)
	$(CC) -o $(CLIENT) $(CLIENT_OBJECTS) $(CFLAGS) $(LDFLAGS)

$(CLIENT_OBJECTS): $(CLIENT_SOURCES) $(CLIENT_HEADERS)
	$(CC) -c $(CLIENT_SOURCES) $(CFLAGS) $(LDFLAGS)

clean:
	$(RM) $(SERVER_OBJECTS)
	$(RM) $(SERVER)
	$(RM) $(CLIENT_OBJECTS)
	$(RM) $(CLIENT)

.PHONY: clean all
