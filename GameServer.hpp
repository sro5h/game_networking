#ifndef GAME_SERVER_HPP
#define GAME_SERVER_HPP

#include "Host.hpp"
#include "Peer.hpp"

#include <SFML/System/Time.hpp>

#include <vector>

class GameServer final
{
public:
        explicit GameServer();

        void update(const sf::Time time);

private:
        void handleEvent(Event& event);
        void handleReceive(Packet& packet, Peer& peer);
        void handleConnect(Peer& peer);
        void handleDisconnect(Peer& peer);

        void incrementTickClock();
        Uint32 now() const;

private:
        Uint32 mTickClock;

        Host mHost;
        std::vector<Peer> mPeers;
};

#endif // GAME_SERVER_HPP
