#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include "Packet.hpp"

namespace cl
{

enum class PacketType : Uint8
{
        Action,
};

Packet& operator<<(Packet&, const PacketType&);
Packet& operator>>(Packet&, PacketType&);

struct ActionPacket
{
        bool MoveUp;
        bool MoveDown;
        bool MoveLeft;
        bool MoveRight;
};

Packet& operator<<(Packet&, const ActionPacket&);
Packet& operator>>(Packet&, ActionPacket&);

}

#endif // PROTOCOL_HPP
