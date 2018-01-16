#ifndef _PEER_HPP_
#define _PEER_HPP_

#include "Event.hpp"

class Peer final
{
public:
        explicit Peer();
        ~Peer();

        bool create();
        void destroy();
        bool connect(const std::string& ip, Uint16 port);
        void disconnect();
        bool pollEvent(Event& event) const;

        void send(const Packet& packet);

private:
        ENetHost* mHost;
        ENetPeer* mRemoteHost;
};

#endif // _PEER_HPP_
