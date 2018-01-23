#include "GameClient.hpp"

#include "Common.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <cassert>

GameClient::GameClient(sf::RenderWindow& window)
        : mTickClock(0)
        , mWindow(window)
        , mShape(20.0f)
{
        mHost.create("localhost", 5354, 1);
        mShape.setOrigin(20.0f, 20.0f);
}

void GameClient::update(const sf::Time time)
{
        incrementTickClock();

        auto actions = collectActions();
        sendActions(actions);

        handleWindowEvents();
        handleNetworkEvents();
}

void GameClient::draw()
{
        mWindow.draw(mShape);
}

void GameClient::connect(const std::string& address, const Uint16 port)
{
        mHost.connect(address, port);
}

void GameClient::waitForConnection()
{
        while (!mPeer)
        {
                handleWindowEvents();

                Event event;
                while (mHost.pollEvent(event))
                {
                        if (event.type == Event::Type::Connect)
                        {
                                mPeer = event.peer;
                        }
                }
        }
}

void GameClient::handleWindowEvents()
{
        sf::Event event;
        while (mWindow.pollEvent(event))
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
}

void GameClient::handleNetworkEvents()
{
        Event event;
        while (mHost.pollEvent(event))
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
}

void GameClient::handleReceive(Packet& packet, const Peer& peer)
{
        sv::PacketType type;
        packet >> type;

        switch (type)
        {
                case sv::PacketType::State:
                {
                        sv::StatePacket state;
                        packet >> state;

                        applyState(state);
                } break;
        }
}

void GameClient::handleConnect(const Peer& peer)
{
        mPeer = peer;
}

void GameClient::handleDisconnect(const Peer& peer)
{
        assert(peer.id == mPeer.id);
}

void GameClient::applyState(const sv::StatePacket& state)
{
        mShape.setPosition(state.states[0].position);
}

cl::ActionPacket GameClient::collectActions() const
{
        cl::ActionPacket actions;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
                actions.MoveUp = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
                actions.MoveDown = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
                actions.MoveLeft = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
                actions.MoveRight = true;
        }

        return actions;
}

void GameClient::sendActions(const cl::ActionPacket& actions)
{
        Packet packet;
        packet << cl::PacketType::Action;
        packet << actions;

        mHost.send(mPeer, packet);
}

void GameClient::incrementTickClock()
{
        ++mTickClock;
}

Uint32 GameClient::now() const
{
        return mTickClock;
}
