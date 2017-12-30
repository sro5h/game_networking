CC=g++
RM=rm
CFLAGS=-I.
LDFLAGS=-lsfml-system -lsfml-window -lsfml-graphics -lsfml-network

PROJECT = app

HEADERS = NetworkProtocol.hpp GameServer.hpp
SOURCES = main.cpp GameServer.cpp
OBJECTS = $(subst .cpp,.o,$(SOURCES))

all: $(PROJECT)

$(PROJECT): $(OBJECTS)
	$(CC) -o $(PROJECT) $(OBJECTS) $(CFLAGS) $(LDFLAGS)

$(OBJECTS): $(SOURCES) $(HEADERS)
	$(CC) -c $(SOURCES) $(CFLAGS) $(LDFLAGS)

clean:
	$(RM) $(OBJECTS)
	$(RM) $(PROJECT)

.PHONY: clean all
