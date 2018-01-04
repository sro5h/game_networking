#ifndef _NETWORK_PROTOCOL_HPP_
#define _NETWORK_PROTOCOL_HPP_

#include <SFML/Config.hpp>

namespace Server
{
const unsigned short Port = 4242;
}

namespace Client
{
enum class Packets : sf::Int32
{
        Disconnect,
};
}

#endif // _NETWORK_PROTOCOL_HPP_
