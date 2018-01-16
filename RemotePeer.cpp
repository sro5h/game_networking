#include "RemotePeer.hpp"

bool RemotePeer::operator==(const RemotePeer& other) const
{
        return other.id == this->id;
}
