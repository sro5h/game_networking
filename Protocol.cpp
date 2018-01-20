#include "Protocol.hpp"

namespace cl
{

Packet& operator<<(Packet& p, const ActionPacket& a)
{
        Uint16 actions = 0;
        actions |= a.MoveUp << 0;
        actions |= a.MoveDown << 1;
        actions |= a.MoveLeft << 2;
        actions |= a.MoveRight << 3;

        return p << actions;
}

Packet& operator>>(Packet& p, ActionPacket& a)
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

}
