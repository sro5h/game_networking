#ifndef _REMOTE_PEER_HPP_
#define _REMOTE_PEER_HPP_

#include "Types.hpp"

#include <string>

struct RemotePeer final
{
public:
        bool operator==(const RemotePeer& other) const;

public:
        std::string address;
        Uint16 port;
        Uint16 id;

private:
        ENetPeer* peer;

        friend class Host;
        friend class Peer;
        friend void toEvent(Event&, const ENetEvent&);
};

#endif // _REMOTE_PEER_HPP_
