#include "Event.hpp"

#include <enet/enet.h>

#include <cassert>

void convertConnect(Event& event, const ENetEvent& enetEvent);
void convertDisconnect(Event& event, const ENetEvent& enetEvent);
void convertReceive(Event& event, const ENetEvent& enetEvent);

std::string convertAddress(const ENetAddress& address);

void toEvent(Event& event, const ENetEvent& enetEvent)
{
        assert(enetEvent.type != ENET_EVENT_TYPE_NONE);

        switch (enetEvent.type)
        {
                case ENET_EVENT_TYPE_CONNECT:
                {
                        convertConnect(event, enetEvent);
                        event.peer.peer = enetEvent.peer;
                } break;

                case ENET_EVENT_TYPE_DISCONNECT:
                {
                        convertDisconnect(event, enetEvent);
                        event.peer.peer = enetEvent.peer;
                } break;

                case ENET_EVENT_TYPE_RECEIVE:
                {
                        convertReceive(event, enetEvent);
                        event.peer.peer = enetEvent.peer;
                } break;

                default:
                {
                        // TODO: log error message, maybe add Type None
                } break;
        }
}

void convertConnect(Event& event, const ENetEvent& enetEvent)
{
        event.type = Event::Type::Connect;
        event.peer.id = enetEvent.peer->incomingPeerID;
        event.peer.address = convertAddress(enetEvent.peer->address);
        event.peer.port = enetEvent.peer->address.port;
}

void convertDisconnect(Event& event, const ENetEvent& enetEvent)
{
        event.type = Event::Type::Disconnect;
        event.peer.id = enetEvent.peer->incomingPeerID;
        event.peer.address = convertAddress(enetEvent.peer->address);
        event.peer.port = enetEvent.peer->address.port;
}

void convertReceive(Event& event, const ENetEvent& enetEvent)
{
        event.type = Event::Type::Receive;
        event.peer.id = enetEvent.peer->incomingPeerID;
        event.peer.address = convertAddress(enetEvent.peer->address);
        event.peer.port = enetEvent.peer->address.port;

        // Copy byte data to Event::packet
        event.packet.append((void*)enetEvent.packet->data, enetEvent.packet->dataLength);

        enet_packet_destroy(enetEvent.packet);
}

std::string convertAddress(const ENetAddress& address)
{
        char buffer[64];
        std::string str;

        if (enet_address_get_host_ip(&address, buffer, sizeof(buffer)) == 0)
        {
                str = buffer;
        }

        return str;
}
