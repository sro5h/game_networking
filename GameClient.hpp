#ifndef GAME_CLIENT_HPP
#define GAME_CLIENT_HPP

#include "Host.hpp"
#include "Peer.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>

class GameClient final
{
public:
        explicit GameClient(sf::RenderWindow& window);

        void update(const sf::Time time);
        void connect(const std::string& address, const Uint16 port);

private:
        void handleWindowEvent(const sf::Event& event);
        void handleNetworkEvent(Event& event);

        void handleReceive(Packet& packet, const Peer& peer);
        void handleConnect(const Peer& peer);
        void handleDisconnect(const Peer& peer);

        void incrementTickClock();
        Uint32 now() const;

private:
        Uint32 mTickClock;

        Host mHost;
        Peer mPeer;

        sf::RenderWindow& mWindow;
};

#endif // GAME_CLIENT_HPP
