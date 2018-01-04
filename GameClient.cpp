#include "GameClient.hpp"
#include "NetworkProtocol.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Packet.hpp>

#include <iostream>

GameClient::GameClient()
        : mConnected(false)
{
        sf::IpAddress ip = "localhost";

        if (mSocket.connect(ip, Server::Port, sf::seconds(5)) == sf::Socket::Done)
        {
                mConnected = true;
        }
        else
        {
                std::cout << "Connection failed" << std::endl;
        }

        mSocket.setBlocking(false);
}

GameClient::~GameClient()
{
        if (mConnected)
        {
                // Inform server this client is quitting
                sf::Packet packet;
                packet << static_cast<sf::Int32>(Client::Packets::Disconnect);
                mSocket.send(packet);

                mSocket.disconnect();
        }
}

void GameClient::run()
{
}

void GameClient::update(sf::Time dt)
{
}
