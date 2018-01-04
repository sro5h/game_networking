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

                typedef std::unique_ptr<RemotePeer> Ptr;
        };

private:
        void update(sf::Time dt);
        void tick(sf::Time dt);

        void handlePackets();
        void handleConnections();
        void handleDisconnections();

        void handlePacket(sf::Packet& packet, RemotePeer& peer);

        void setListening(bool enable);
        // Returns the current tick counter
        sf::Int32 now() const;

private:
        const sf::Time mUpdateInterval;
        const unsigned short mPort;

        sf::Int32 mTickCounter;
        bool mIsRunning;
        bool mIsListening;

        sf::TcpListener mListenerSocket;

        std::size_t mMaxConnections;
        std::size_t mConnectionCount;

        std::vector<RemotePeer::Ptr> mPeers;
};

#endif // _GAME_SERVER_HPP_
