#ifndef _GAME_CLIENT_HPP_
#define _GAME_CLIENT_HPP_

#include <SFML/Network/TcpSocket.hpp>

class GameClient
{
public:
        explicit GameClient();
        ~GameClient();

        void run();

private:
        void update(sf::Time dt);

        void handlePackets();
        void handlePacket(sf::Packet& packet);

private:
        const sf::Time mUpdateInterval;

        bool mIsRunning;
        bool mConnected;
        sf::TcpSocket mSocket;

        sf::Int32 mId;
};

#endif // _GAME_CLIENT_HPP_
