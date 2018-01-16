#ifndef _HOST_HPP_
#define _HOST_HPP_

#include "Event.hpp"

class Host final
{
public:
        explicit Host();
        ~Host();

        bool create(const std::string& address, const Uint16 port, const std::size_t maxPeers);
        void destroy();
        void disconnect(const RemotePeer& peer);
        void disconnectAll();
        bool pollEvent(Event& event) const;
        std::size_t getConnectedPeerCount() const;

        void broadcast(const Packet& packet);
        void broadcastExcept(const RemotePeer& peer, const Packet& packet);
        void send(const RemotePeer& peer, const Packet& packet);

private:
        ENetHost* mHost;
};

#endif // _HOST_HPP_
