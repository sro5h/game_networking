#ifndef _PACKET_HPP_
#define _PACKET_HPP_

#include "Types.hpp"

#include <string>
#include <vector>

class Packet
{
public:
        enum class Flag : Uint16;

public:
        Packet(Flag flag = Flag::Unreliable);
        ~Packet();

        void append(const void* data, std::size_t size);
        void clear();
        const void* getData() const;
        std::size_t getDataSize() const;
        bool dataLeft() const;

public:
        explicit operator bool() const;

        Packet& operator>>(bool& data);
        Packet& operator>>(Int8& data);
        Packet& operator>>(Uint8& data);
        Packet& operator>>(Int16& data);
        Packet& operator>>(Uint16& data);
        Packet& operator>>(Int32& data);
        Packet& operator>>(Uint32& data);
        Packet& operator>>(float& data);
        Packet& operator>>(double& data);
        Packet& operator>>(char* data);
        Packet& operator>>(std::string& data);

        Packet& operator<<(bool data);
        Packet& operator<<(Int8 data);
        Packet& operator<<(Uint8 data);
        Packet& operator<<(Int16 data);
        Packet& operator<<(Uint16 data);
        Packet& operator<<(Int32 data);
        Packet& operator<<(Uint32 data);
        Packet& operator<<(float data);
        Packet& operator<<(double data);
        Packet& operator<<(const char* data);
        Packet& operator<<(const std::string& data);

public:
        enum class Flag : Uint16
        {
                Reliable,
                Unreliable,
                Unsequenced,
        };

public:
        Flag flag;

private:
        bool operator==(const Packet& p) const;
        bool operator!=(const Packet& p) const;

        bool checkSize(std::size_t size);

        std::vector<char> mData;
        std::size_t mReadPos;
        bool mIsValid;
};

ENetPacket* toENetPacket(const Packet& packet);

#endif // _PACKET_HPP_
