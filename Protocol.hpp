#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include "Packet.hpp"

namespace cl
{

enum class PacketType : Uint8
{
        Action,
};

struct ActionPacket
{
        bool MoveUp;
        bool MoveDown;
        bool MoveLeft;
        bool MoveRight;
};

Packet& operator<<(Packet& p, const ActionPacket& a);
Packet& operator>>(Packet& p, ActionPacket& a);

}

#endif // PROTOCOL_HPP
