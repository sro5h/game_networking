#include "ClientProtocol.hpp"

Packet& cl::operator<<(Packet& p, const cl::PacketType& pt)
{
        return p << static_cast<Uint8>(pt);
}

Packet& cl::operator>>(Packet& p, cl::PacketType& pt)
{
        Uint8 data;
        if (p >> data)
        {
                pt = static_cast<cl::PacketType>(data);
        }

        return p;
}

Packet& cl::operator<<(Packet& p, const cl::ActionPacket& a)
{
        Uint16 actions = 0;
        actions |= a.MoveUp << 0;
        actions |= a.MoveDown << 1;
        actions |= a.MoveLeft << 2;
        actions |= a.MoveRight << 3;

        return p << actions;
}

Packet& cl::operator>>(Packet& p, cl::ActionPacket& a)
{
        Uint16 actions = 0;
        if (p >> actions)
        {
                a.MoveUp = actions & (1 << 0);
                a.MoveDown = actions & (1 << 1);
                a.MoveLeft = actions & (1 << 2);
                a.MoveRight = actions & (1 << 3);
        }

        return p;
}

