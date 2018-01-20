#ifndef GAME_SERVER_HPP
#define GAME_SERVER_HPP

#include "Protocol.hpp"
#include "Host.hpp"
#include "Peer.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

#include <map>
#include <vector>

struct Player final
{
        cl::ActionPacket actions;
        sf::Vector2f position;
};

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

        void updatePlayers();

        void incrementTickClock();
        Uint32 now() const;

private:
        Uint32 mTickClock;

        Host mHost;
        std::vector<Peer> mPeers;
        std::map<Uint16, Player> mPlayers;
};

#endif // GAME_SERVER_HPP
