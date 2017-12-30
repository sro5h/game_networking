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

private:
        bool mConnected;
        sf::TcpSocket mSocket;
};

#endif // _GAME_CLIENT_HPP_
