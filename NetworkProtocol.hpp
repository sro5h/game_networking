#ifndef _NETWORK_PROTOCOL_HPP_
#define _NETWORK_PROTOCOL_HPP_

#include <SFML/Config.hpp>

namespace Server
{
const unsigned short Port = 4242;

enum class Packets : sf::Int32
{
        ConnectedSelf,
        Connected,
};
}

namespace Client
{
enum class Packets : sf::Int32
{
        Disconnect,     // format: [Int32:packetType]
};
}

#endif // _NETWORK_PROTOCOL_HPP_
