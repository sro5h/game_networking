#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include "Packet.hpp"

#include <SFML/System/Vector2.hpp>

#include <vector>

namespace sv
{

enum class PacketType : Uint8
{
        State,
};

Packet& operator<<(Packet&, const PacketType&);
Packet& operator>>(Packet&, PacketType&);

struct PlayerState
{
        Uint16 id;
        sf::Vector2f position;
};

struct StatePacket
{
        Uint8 count;
        std::vector<PlayerState> states;
};

Packet& operator<<(Packet&, const StatePacket&);
Packet& operator>>(Packet&, StatePacket&);

}

#endif // PROTOCOL_HPP
