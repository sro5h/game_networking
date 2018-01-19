#include "GameClient.hpp"

#include "Common.hpp"

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
        logEvent(event);

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
}

void GameClient::handleConnect(const Peer& peer)
{
        mPeer = peer;
}

void GameClient::handleDisconnect(const Peer& peer)
{
        assert(peer.id == mPeer.id);
}

void GameClient::incrementTickClock()
{
        ++mTickClock;
}

Uint32 GameClient::now() const
{
        return mTickClock;
}
