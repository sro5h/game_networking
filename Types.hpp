#ifndef TYPES_HPP
#define TYPES_HPP

#include <cstdint>

// Forward declarations of enet types
typedef struct _ENetHost ENetHost;
typedef struct _ENetPeer ENetPeer;
typedef struct _ENetPacket ENetPacket;
typedef struct _ENetEvent ENetEvent;

struct Event;

// Fixed size integral types
typedef std::int8_t Int8;
typedef std::uint8_t Uint8;
typedef std::int16_t Int16;
typedef std::uint16_t Uint16;
typedef std::int32_t Int32;
typedef std::uint32_t Uint32;

#endif // TYPES_HPP
