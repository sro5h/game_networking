CXX = g++
RM = rm
CXXFLAGS = -I. -Wall -Wextra -std=c++14
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lenet

PROJECT = app
PROJECT_HEADERS = Event.hpp Packet.hpp Host.hpp Peer.hpp GameServer.hpp\
                  GameClient.hpp Common.hpp ClientProtocol.hpp\
                  ServerProtocol.hpp
PROJECT_SOURCES = main.cpp Event.cpp Packet.cpp Host.cpp Peer.cpp\
                  GameServer.cpp GameClient.cpp Common.cpp ClientProtocol.cpp\
                  ServerProtocol.cpp
PROJECT_OBJECTS = $(subst .cpp,.o,$(PROJECT_SOURCES))

all: $(PROJECT)

$(PROJECT): $(PROJECT_OBJECTS)
	$(CXX) -o $(PROJECT) $(PROJECT_OBJECTS) $(CXXFLAGS) $(LDFLAGS)

$(PROJECT_OBJECTS): $(PROJECT_SOURCES) $(PROJECT_HEADERS)
	$(CXX) -c $(PROJECT_SOURCES) $(CXXFLAGS) $(LDFLAGS)

clean:
	$(RM) $(PROJECT_OBJECTS)
	$(RM) $(PROJECT)

.PHONY: clean all
