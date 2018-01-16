#include "Peer.hpp"

#include <enet/enet.h>

Peer::Peer()
        : peer(nullptr)
{
}

bool Peer::operator==(const Peer& other) const
{
        return other.id == this->id;
}
