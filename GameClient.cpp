#include "GameClient.hpp"
#include "NetworkProtocol.hpp"

#include <SFML/Network/IpAddress.hpp>

#include <iostream>

GameClient::GameClient()
        : mConnected(false)
{
        sf::IpAddress ip = "127.0.0.1";

        if (mSocket.connect(ip, Server::Port) == sf::TcpSocket::Done)
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
        // TODO: send a disconnection packet
        if (mConnected)
                mSocket.disconnect();
}

void GameClient::run()
{
}

void GameClient::update(sf::Time dt)
{
}
