#include "Peer.hpp"
#include <enet/enet.h>

Peer::Peer()
        : peer(nullptr)
{
}

State Peer::getState()
{
        if (!peer)
        {
                return State::Zombie;
        }

        switch (peer->state)
        {
                case ENET_PEER_STATE_ZOMBIE:
                        return State::Zombie;

                case ENET_PEER_STATE_DISCONNECTED:
                        return State::Disconnected;

                case ENET_PEER_STATE_DISCONNECTING:
                        return State::Disconnecting;

                case ENET_PEER_STATE_ACKNOWLEDGING_DISCONNECT:
                        return State::AcknowlegdingDisconnect;

                case ENET_PEER_STATE_DISCONNECT_LATER:
                        return State::DisconnectLater;

                case ENET_PEER_STATE_CONNECTED:
                        return State::Connected;

                case ENET_PEER_STATE_CONNECTING:
                        return State::Connecting;

                case ENET_PEER_STATE_ACKNOWLEDGING_CONNECT:
                        return State::AcknowledgingConnect;

                case ENET_PEER_STATE_CONNECTION_PENDING:
                        return State::PendingConnect;

                case ENET_PEER_STATE_CONNECTION_SUCCEEDED:
                        return State::Succeeded;

                default:
                        return State::Zombie;
        }
}

bool Peer::operator==(const Peer& other) const
{
        if (peer != nullptr && other.peer != nullptr)
        {
                return other.id == id;
        }

        return false;
}

Peer::operator bool() const
{
        return peer != nullptr;
}
