#include "GameClient.hpp"
#include "NetworkProtocol.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Packet.hpp>

#include <iostream>

GameClient::GameClient()
        : mUpdateInterval(sf::milliseconds(100))
        , mIsRunning(true)
        , mConnected(false)
        , mId(-1)
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
        sf::Time accumulator = sf::Time::Zero;
        sf::Clock updateClock;

        while (mIsRunning)
        {
                accumulator += updateClock.restart();

                while (accumulator >= mUpdateInterval)
                {
                        accumulator -= mUpdateInterval;

                        handlePackets();

                        update(mUpdateInterval);
                }
        }
}

void GameClient::update(sf::Time dt)
{
}

void GameClient::handlePackets()
{
        sf::Packet packet;

        while (mSocket.receive(packet) == sf::Socket::Done)
        {
                // Interpret packet and react to it
                handlePacket(packet);

                // TODO: update ping timer of peer

                packet.clear();
        }
}

void GameClient::handlePacket(sf::Packet& packet)
{
        sf::Int32 typeData;
        packet >> typeData;

        Server::Packets packetType = static_cast<Server::Packets>(typeData);

        switch (packetType)
        {
                case Server::Packets::ConnectedSelf:
                {
                        packet >> mId;
                        std::cout << "Id = " << mId << std::endl;
                } break;

                case Server::Packets::Connected:
                {
                        sf::Int32 id;
                        packet >> id;
                        std::cout << "New connection id = " << id << std::endl;
                } break;
        }
}
