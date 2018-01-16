#ifndef PEER_HPP
#define PEER_HPP

#include "Types.hpp"

#include <string>

struct Peer final
{
public:
        explicit Peer();

public:
        bool operator==(const Peer& other) const;

public:
        std::string address;
        Uint16 port;
        Uint16 id;

private:
        ENetPeer* peer;

        friend class Host;
        friend void convertPeer(Peer&, const ENetPeer&);
};

#endif // PEER_HPP
