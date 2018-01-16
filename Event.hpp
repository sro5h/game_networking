#ifndef _EVENT_HPP_
#define _EVENT_HPP_

#include "Packet.hpp"
#include "RemotePeer.hpp"

struct Event final
{
        enum class Type : Uint16
        {
                Connect,
                Disconnect,
                Receive,
        } type;

        RemotePeer peer;
        Packet packet;
};

void toEvent(Event& event, const ENetEvent& enetEvent);

#endif // _EVENT_HPP_
