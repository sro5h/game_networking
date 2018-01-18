#include "GameClient.hpp"

#include <iostream>
#include <cassert>

GameClient::GameClient()
        : mTickClock(0)
{
        mHost.create("localhost", 5354, 1);
}

void GameClient::update(const sf::Time time)
{
        incrementTickClock();

        Event event;
        while (mHost.pollEvent(event))
        {
                handleEvent(event);
        }
}

void GameClient::connect(const std::string& address, const Uint16 port)
{
        mHost.connect(address, port);
}

void GameClient::handleEvent(Event& event)
{
        switch (event.type)
        {
                case Event::Type::Receive:
                {
                        handleReceive(event.packet, event.peer);
                } break;

                case Event::Type::Connect:
                {
                        handleConnect(event.peer);
                } break;

                case Event::Type::Disconnect:
                {
                        handleDisconnect(event.peer);
                } break;
        }
}

void GameClient::handleReceive(Packet& packet, const Peer& peer)
{
        std::cout << "Receive" << std::endl;
}

void GameClient::handleConnect(const Peer& peer)
{
        mPeer = peer;
        std::cout << "Connect" << std::endl;
}

void GameClient::handleDisconnect(const Peer& peer)
{
        assert(peer.id == mPeer.id);
        std::cout << "Disconnect" << std::endl;
}

void GameClient::incrementTickClock()
{
        ++mTickClock;
}

Uint32 GameClient::now() const
{
        return mTickClock;
}
