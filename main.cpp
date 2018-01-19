#include "GameServer.hpp"
#include "GameClient.hpp"

#include <SFML/System/Clock.hpp>
#include <enet/enet.h>

#include <iostream>

#define SERVER_PORT 42323

const sf::Time interval = sf::milliseconds(50);

void runGameServer();
void runGameClient();

int main(int argc, char* argv[])
{
        if (enet_initialize() != 0)
        {
                std::cerr << "Could not initialize enet." << std::endl;
                return EXIT_FAILURE;
        }

        std::string mode = "s";
        if (argc > 1)
        {
                mode = argv[1];
        }

        if (mode == "s")
        {
                runGameServer();
        }
        else
        {
                runGameClient();
        }

        return 0;
}

void runGameServer()
{
        GameServer server;
        sf::Clock clock;
        sf::Time accumulator = sf::Time::Zero;

        std::cout << "Server started." << std::endl;

        while (true)
        {
                accumulator += clock.restart();

                while (accumulator >= interval)
                {
                        accumulator -= interval;

                        server.update(interval);
                }
        }
}

void runGameClient()
{
        sf::RenderWindow window(sf::VideoMode(400, 400), "App");
        GameClient client(window);

        sf::Clock clock;
        sf::Time accumulator = sf::Time::Zero;

        std::cout << "Client started." << std::endl;

        client.connect("localhost", 4243);

        while (window.isOpen())
        {
                accumulator += clock.restart();

                while (accumulator >= interval)
                {
                        accumulator -= interval;

                        client.update(interval);
                }

                window.clear();
                window.display();
        }
}
