#ifndef HOST_HPP
#define HOST_HPP

#include "Event.hpp"

class Host final
{
public:
        explicit Host();
        ~Host();

        bool create(const std::string& address, const Uint16 port, const std::size_t connections);
        void destroy();
        bool connect(const std::string& address, const Uint16 port);
        void disconnect(const Peer& peer);
        void disconnectAll();
        bool pollEvent(Event& event) const;
        std::size_t getConnectionCount() const;

        void broadcast(const Packet& packet);
        void broadcastExcept(const Peer& peer, const Packet& packet);
        void send(const Peer& peer, const Packet& packet);

private:
        ENetHost* mHost;
};

#endif // HOST_HPP
