#ifndef HOST_HPP
#define HOST_HPP

#include "Event.hpp"

/**
 * Manages connections and sends Packets to connected Peers.
 */
class Host final
{
public:
        /**
         * Initializes the Host to an invalid state.
         */
        explicit Host();

        /**
         * Cleans up the ENetHost and its connected ENetPeers if needed.
         */
        ~Host();

        /**
         * Creates the Host on address:port with a maximum of connections
         * imcoming peer connections.
         * @param address The address to create the Host on
         * @param port The port to create the Host on
         * @param connections The maximum amount of connections to accept
         * @return True if successful
         */
        bool create(const std::string& address, const Uint16 port, const std::size_t connections);

        /**
         * Cleans up the ENetHost and its connected ENetPeers if needed and
         * leaves the Host in an invalid state.
         */
        void destroy();

        /**
         * Attempts a connection with a Peer on address:port.
         * @param address The address to connect to
         * @param port The port to connect to
         * return True if an attempt was made
         */
        bool connect(const std::string& address, const Uint16 port);

        /**
         * Attempts a disconnection from a connected Peer.
         * @param peer The Peer to disconnect from
         */
        void disconnect(const Peer& peer);

        /**
         * Attempts a disconnection from all connected Peers.
         */
        void disconnectAll();

        /**
         * Polls the Host for incoming Events.
         * @param event The Event
         * @return True if an Event was found
         */
        bool pollEvent(Event& event) const;

        /**
         * Get the number of connected Peers.
         * @return The number of connected Peers
         */
        std::size_t getConnectionCount() const;

        /**
         * Send a Packet to all connected Peers.
         * @param packet The Packet to send
         */
        void broadcast(const Packet& packet);

        /**
         * Sends a Packet to all connected Peers except one.
         * @param peer The Peer to ignore
         * @param packet The Packet to send
         */
        void broadcastExcept(const Peer& peer, const Packet& packet);

        /**
         * Sends a Packet to the specified Peer.
         * @param peer The Peer to send the Packet to
         * @param packet The Packet to send
         */
        void send(const Peer& peer, const Packet& packet);

private:
        ENetHost* mHost;
};

#endif // HOST_HPP
