#ifndef _GAME_SERVER_HPP_
#define _GAME_SERVER_HPP_

#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/TcpListener.hpp>

#include <memory>
#include <vector>

class GameServer
{
public:
        explicit GameServer();

        void run();

private:
        struct RemotePeer
        {
                explicit RemotePeer();

                sf::TcpSocket socket;
                bool connected;
                sf::Int32 id;
                sf::Int32 lastPacketTick;

                typedef std::unique_ptr<RemotePeer> Ptr;
        };

private:
        void update(sf::Time dt);
        void tick(sf::Time dt);

        void handlePackets();
        void handleConnections();
        void handleDisconnections();

        void handlePacket(sf::Packet& packet, RemotePeer& peer);
        void notifyConnection(RemotePeer& newPeer);

        void broadcast(sf::Packet& packet);
        void broadcastExcept(sf::Int32 peerId, sf::Packet& packet);

        void setListening(bool enable);
        // Returns the current tick counter
        sf::Int32 now() const;

private:
        const sf::Time mUpdateInterval;
        const sf::Int32 mTimeoutTicks;
        const unsigned short mPort;

        sf::Int32 mTickCounter;
        sf::Int32 mIdCounter;
        bool mIsRunning;
        bool mIsListening;

        sf::TcpListener mListenerSocket;

        std::size_t mMaxConnections;
        std::size_t mConnectionCount;

        std::vector<RemotePeer::Ptr> mPeers;
};

#endif // _GAME_SERVER_HPP_
