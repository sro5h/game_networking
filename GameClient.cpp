#include "GameClient.hpp"

#include "Common.hpp"

#include <SFML/Window/Event.hpp>

#include <cassert>

GameClient::GameClient(sf::RenderWindow& window)
        : mTickClock(0)
        , mWindow(window)
{
        mHost.create("localhost", 5354, 1);
}

void GameClient::update(const sf::Time time)
{
        incrementTickClock();

        sf::Event windowEvent;
        while (mWindow.pollEvent(windowEvent))
        {
                handleWindowEvent(windowEvent);
        }

        Event netEvent;
        while (mHost.pollEvent(netEvent))
        {
                handleNetworkEvent(netEvent);
        }
}

void GameClient::connect(const std::string& address, const Uint16 port)
{
        mHost.connect(address, port);
}

void GameClient::handleWindowEvent(const sf::Event& event)
{
        switch (event.type)
        {
                case sf::Event::Closed:
                {
                        mWindow.close();
                } break;

                default:
                        break;
        }
}

void GameClient::handleNetworkEvent(Event& event)
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
