#ifndef EVENT_HPP
#define EVENT_HPP

#include "Packet.hpp"
#include "Peer.hpp"

struct Event final
{
        enum class Type : Uint16
        {
                Connect,
                Disconnect,
                Receive,
        } type;

        Peer peer;
        Packet packet;
};

void toEvent(Event& event, const ENetEvent& enetEvent);

#endif // EVENT_HPP
