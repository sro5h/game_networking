#include "Peer.hpp"

#include <enet/enet.h>

Peer::Peer()
        : peer(nullptr)
{
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
