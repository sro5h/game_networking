#ifndef GAME_CLIENT_HPP
#define GAME_CLIENT_HPP

#include "ClientProtocol.hpp"
#include "ServerProtocol.hpp"
#include "Host.hpp"
#include "Peer.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>

class GameClient final
{
public:
        explicit GameClient(sf::RenderWindow& window);

        void update(const sf::Time time);
        void draw();
        void connect(const std::string& address, const Uint16 port);
        void waitForConnection();

private:
        void handleWindowEvents();
        void handleNetworkEvents();

        void handleReceive(Packet& packet, const Peer& peer);
        void handleConnect(const Peer& peer);
        void handleDisconnect(const Peer& peer);

        cl::ActionPacket collectActions() const;
        void sendActions(const cl::ActionPacket& actions);
        void applyState(const sv::StatePacket& state);

        void incrementTickClock();
        Uint32 now() const;

private:
        Uint32 mTickClock;

        Host mHost;
        Peer mPeer;

        sf::RenderWindow& mWindow;
        sf::CircleShape mShape;
};

#endif // GAME_CLIENT_HPP
