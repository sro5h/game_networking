#ifndef EVENT_HPP
#define EVENT_HPP

#include "Packet.hpp"
#include "Peer.hpp"

/**
 * Holds all relevant data of the according ENetEvent.
 */
struct Event final
{
        /**
         * The type of the Event, maps to an ENetEventType.
         */
        enum class Type : Uint16
        {
                Connect,
                Disconnect,
                Receive,
        } type;

        Peer peer;
        Packet packet;
};

/**
 * A helper function to convert an ENetEvent to an Event.
 * @param event The Event to convert to
 * @param enetEvent The ENetEvent to convert from
 */
void toEvent(Event& event, const ENetEvent& enetEvent);

#endif // EVENT_HPP
