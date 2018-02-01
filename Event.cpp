#include "Event.hpp"
#include <enet/enet.h>
#include <cassert>

void convertPeer(Peer& peer, const ENetPeer& enetPeer);
std::string convertAddress(const ENetAddress& address);

void toEvent(Event& event, const ENetEvent& enetEvent)
{
        assert(enetEvent.type != ENET_EVENT_TYPE_NONE);

        switch (enetEvent.type)
        {
                case ENET_EVENT_TYPE_CONNECT:
                {
                        event.type = Event::Type::Connect;
                        convertPeer(event.peer, *enetEvent.peer);
                        event.peer.peer = enetEvent.peer;
                } break;

                case ENET_EVENT_TYPE_DISCONNECT:
                {
                        event.type = Event::Type::Disconnect;
                        convertPeer(event.peer, *enetEvent.peer);
                        event.peer.peer = enetEvent.peer;
                } break;

                case ENET_EVENT_TYPE_RECEIVE:
                {
                        event.type = Event::Type::Receive;
                        event.packet.append((void*)enetEvent.packet->data,
                                        enetEvent.packet->dataLength);
                        convertPeer(event.peer, *enetEvent.peer);
                        event.peer.peer = enetEvent.peer;

                        enet_packet_destroy(enetEvent.packet);
                } break;

                default:
                {
                        // TODO: log error message, maybe add Type None
                } break;
        }
}

void convertPeer(Peer& peer, const ENetPeer& enetPeer)
{
        peer.id = enetPeer.incomingPeerID;
        peer.outgoingId = enetPeer.outgoingPeerID;
        peer.address = convertAddress(enetPeer.address);
        peer.port = enetPeer.address.port;
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
