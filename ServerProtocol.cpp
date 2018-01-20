#include "ServerProtocol.hpp"

Packet& sv::operator<<(Packet& p, const sv::PacketType& pt)
{
        return p << static_cast<Uint8>(pt);
}

Packet& sv::operator>>(Packet& p, sv::PacketType& pt)
{
        Uint8 data;
        if (p >> data)
        {
                pt = static_cast<sv::PacketType>(data);
        }

        return p;
}

Packet& sv::operator<<(Packet& p, const sv::StatePacket& sp)
{
        p << sp.count;

        for (const auto& state : sp.states)
        {
                p << state.id << state.position.x << state.position.y;
        }

        return p;
}

Packet& sv::operator>>(Packet& p, sv::StatePacket& sp)
{
        Uint8 count;
        if (p >> count)
        {
                sp.count = count;

                for (; count > 0; count--)
                {
                        sv::PlayerState state;
                        p >> state.id;
                        p >> state.position.x >> state.position.y;
                        sp.states.push_back(state);
                }
        }

        return p;
}
