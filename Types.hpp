#ifndef _TYPES_HPP_
#define _TYPES_HPP_

#include <cstdint>

typedef struct _ENetHost ENetHost;
typedef struct _ENetPeer ENetPeer;
typedef struct _ENetPacket ENetPacket;
typedef struct _ENetEvent ENetEvent;

struct Event;

// Fixed size integers
typedef std::int8_t Int8;
typedef std::uint8_t Uint8;
typedef std::int16_t Int16;
typedef std::uint16_t Uint16;
typedef std::int32_t Int32;
typedef std::uint32_t Uint32;

#endif // _TYPES_HPP_
