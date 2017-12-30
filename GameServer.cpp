#include "GameServer.hpp"
#include "NetworkProtocol.hpp"

#include <SFML/System/Clock.hpp>
#include <SFML/Network/Packet.hpp>

#include <iostream>

GameServer::RemotePeer::RemotePeer()
        : connected(false)
{
        socket.setBlocking(false);
}

GameServer::GameServer()
        : mUpdateInterval(sf::milliseconds(100))
        , mPort(Server::Port)
        , mTickCounter(0)
        , mIsRunning(true)
        , mMaxConnections(2)
        , mConnectionCount(0)
{
        mListenerSocket.setBlocking(false);
        setListening(true);
}

void GameServer::run()
{
        sf::Time accumulator = sf::Time::Zero;
        sf::Clock updateClock;

        while (mIsRunning)
        {
                accumulator += updateClock.restart();

                while (accumulator >= mUpdateInterval)
                {
                        accumulator -= mUpdateInterval;
                        ++mTickCounter;

                        handleConnections();
                        handleDisconnections();

                        update(mUpdateInterval);
                        tick(mUpdateInterval);
                }
        }
}

void GameServer::update(sf::Time dt)
{
}

void GameServer::tick(sf::Time dt)
{
}

void GameServer::handleConnections()
{
        if (!mIsListening)
                return;

        RemotePeer::Ptr newPeer = std::make_unique<RemotePeer>();

        if (mListenerSocket.accept(newPeer->socket) == sf::TcpListener::Done)
        {
                std::cout << "New connection" << std::endl;

                mPeers.push_back(std::move(newPeer));
                mPeers.back()->connected = true;

                ++mConnectionCount;

                if (mConnectionCount >= mMaxConnections)
                        setListening(false);
        }
}

void GameServer::handleDisconnections()
{
        for (auto itr = mPeers.begin(); itr != mPeers.end(); )
        {
                if (!(*itr)->connected)
                {
                        std::cout << "Connection lost" << std::endl;

                        itr = mPeers.erase(itr);
                        --mConnectionCount;

                        if (mConnectionCount < mMaxConnections)
                                setListening(true);
                }
                else
                {
                        ++itr;
                }
        }
}

void GameServer::setListening(bool enable)
{
        if (enable && !mIsListening)
        {
                mIsListening = (mListenerSocket.listen(mPort) == sf::TcpListener::Done);
        }
        else
        {
                mListenerSocket.close();
                mIsListening = false;
        }
}

sf::Int32 GameServer::now() const
{
        return mTickCounter;
}
