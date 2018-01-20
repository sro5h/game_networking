#ifndef CLIENT_PROTOCOL_HPP
#define CLIENT_PROTOCOL_HPP

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

#endif // CLIENT_PROTOCOL_HPP
