#include "GameServer.hpp"

#include "Common.hpp"

#include <algorithm>
#include <cassert>

GameServer::GameServer()
        : mTickClock(0)
{
        mHost.create("localhost", 4243, 5);
}

void GameServer::update(const sf::Time time)
{
        incrementTickClock();

        Event event;
        while (mHost.pollEvent(event))
        {
                handleEvent(event);
        }
}

void GameServer::handleEvent(Event& event)
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

void GameServer::handleReceive(Packet& packet, Peer& peer)
{
}

void GameServer::handleConnect(Peer& peer)
{
        mPeers.push_back(peer);
}

void GameServer::handleDisconnect(Peer& peer)
{
        auto it = std::find(mPeers.begin(), mPeers.end(), peer);

        assert(it != mPeers.end());

        if (it != mPeers.end())
        {
                mPeers.erase(it);
        }
}

void GameServer::incrementTickClock()
{
        ++mTickClock;
}

Uint32 GameServer::now() const
{
        return mTickClock;
}
