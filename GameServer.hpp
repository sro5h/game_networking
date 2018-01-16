#ifndef GAME_SERVER_HPP
#define GAME_SERVER_HPP

#include "Host.hpp"

#include <SFML/System/Time.hpp>

#include <vector>

class GameServer final
{
public:
        explicit GameServer();

        void update(const sf::Time time);

private:
        void handleEvent(Event& event);
        void handleReceive(Packet& packet, RemotePeer& peer);
        void handleConnect(RemotePeer& peer);
        void handleDisconnect(RemotePeer& peer);

        void incrementTickClock();
        Uint32 now() const;

private:
        Uint32 mTickClock;

        Host mHost;
        std::vector<RemotePeer> mPeers;
};

#endif // GAME_SERVER_HPP
