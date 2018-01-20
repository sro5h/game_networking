#include "GameServer.hpp"

#include "Common.hpp"

#include <algorithm>
#include <iostream>
#include <cassert>

const int playerSpeed = 4;

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

        updatePlayers();
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
        cl::PacketType type;
        packet >> type;

        switch (type)
        {
                case cl::PacketType::Action:
                {
                        cl::ActionPacket actions;
                        packet >> actions;
                        mPlayers[peer.id].actions = actions;
                        std::cout << "ActionPacket" << std::endl;
                } break;
        }
}

void GameServer::handleConnect(Peer& peer)
{
        mPeers.push_back(peer);
        mPlayers[peer.id] = Player();
}

void GameServer::handleDisconnect(Peer& peer)
{
        int rc = mPlayers.erase(peer.id);
        assert(rc != 0);

        auto it = std::find(mPeers.begin(), mPeers.end(), peer);
        assert(it != mPeers.end());

        if (it != mPeers.end())
        {
                mPeers.erase(it);
        }
}

void GameServer::updatePlayers()
{
        for (auto& entry : mPlayers)
        {
                Player& p = entry.second;
                if (p.actions.MoveUp)
                {
                        p.position.y -= playerSpeed;
                }
                if (p.actions.MoveDown)
                {
                        p.position.y += playerSpeed;
                }
                if (p.actions.MoveLeft)
                {
                        p.position.x -= playerSpeed;
                }
                if (p.actions.MoveRight)
                {
                        p.position.x += playerSpeed;
                }
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
