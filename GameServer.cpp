#include "GameServer.hpp"
#include "NetworkProtocol.hpp"

#include <SFML/System/Clock.hpp>
#include <SFML/Network/Packet.hpp>

#include <iostream>

GameServer::RemotePeer::RemotePeer()
        : connected(false)
        , lastPacketTick(0)
{
        socket.setBlocking(false);
}

GameServer::GameServer()
        : mUpdateInterval(sf::milliseconds(100))
        , mTimeoutTicks(20)
        , mPort(Server::Port)
        , mTickCounter(0)
        , mIdCounter(0)
        , mIsRunning(true)
        , mMaxConnections(5)
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

                        handlePackets();
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

void GameServer::handlePackets()
{
        for (RemotePeer::Ptr& peer : mPeers)
        {
                sf::Packet packet;

                while (peer->socket.receive(packet) == sf::Socket::Done)
                {
                        // Interpret packet and react to it
                        handlePacket(packet, *peer);

                        peer->lastPacketTick = now();
                        packet.clear();
                }

                // Check if peer timed out
                if (now() >= peer->lastPacketTick + mTimeoutTicks)
                {
                        peer->connected = false;
                }
        }
}

void GameServer::handleConnections()
{
        if (!mIsListening)
                return;

        RemotePeer::Ptr newPeer = std::make_unique<RemotePeer>();

        if (mListenerSocket.accept(newPeer->socket) == sf::TcpListener::Done)
        {
                std::cout << "New connection (";
                std::cout << newPeer->socket.getRemoteAddress();
                std::cout << ":" << newPeer->socket.getRemotePort() << ")";
                std::cout << std::endl;

                mPeers.push_back(std::move(newPeer));
                mPeers.back()->connected = true;
                mPeers.back()->id = mIdCounter;
                // prevent initial timeout
                mPeers.back()->lastPacketTick = now();

                notifyConnection(*mPeers.back());

                ++mConnectionCount;
                ++mIdCounter;

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

                        (*itr)->socket.disconnect();

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

void GameServer::handlePacket(sf::Packet& packet, RemotePeer& peer)
{
        sf::Int32 typeData;
        packet >> typeData;

        Client::Packets packetType = static_cast<Client::Packets>(typeData);

        switch (packetType)
        {
                case Client::Packets::Disconnect:
                        peer.connected = false;
                        break;
        }
}

void GameServer::notifyConnection(RemotePeer& newPeer)
{
        // Notify the peer itself
        sf::Packet selfPacket;
        selfPacket << static_cast<sf::Int32>(Server::Packets::ConnectedSelf);
        selfPacket << newPeer.id;
        newPeer.socket.send(selfPacket);

        // Notify other peers
        sf::Packet othersPacket;
        othersPacket << static_cast<sf::Int32>(Server::Packets::Connected);
        othersPacket << newPeer.id;
        broadcastExcept(newPeer.id, othersPacket);
}

void GameServer::broadcast(sf::Packet& packet)
{
        for (RemotePeer::Ptr& peer : mPeers)
        {
                peer->socket.send(packet);
        }
}

void GameServer::broadcastExcept(sf::Int32 peerId, sf::Packet& packet)
{
        for (RemotePeer::Ptr& peer : mPeers)
        {
                if (peer->id != peerId)
                {
                        peer->socket.send(packet);
                }
        }
}

void GameServer::setListening(bool enable)
{
        if (enable && !mIsListening)
        {
                mIsListening = (mListenerSocket.listen(mPort) == sf::TcpListener::Done);
        }
        else if (!enable && mIsListening)
        {
                mListenerSocket.close();
                mIsListening = false;
        }
}

sf::Int32 GameServer::now() const
{
        return mTickCounter;
}
