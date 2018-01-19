#include "Packet.hpp"

#include <enet/enet.h>

#include <cstring>

Packet::Packet(Flag flag)
        : flag(flag)
        , mReadPos(0)
        , mIsValid(true)
{
}

void Packet::append(const void* data, std::size_t size)
{
        if (data && (size > 0))
        {
                std::size_t start = mData.size();
                mData.resize(start + size);
                std::memcpy(&mData[start], data, size);
        }
}

void Packet::clear()
{
        mData.clear();
        mReadPos = 0;
        mIsValid = true;
}

const void* Packet::getData() const
{
        return !mData.empty() ? &mData[0] : nullptr;
}

std::size_t Packet::getDataSize() const
{
        return mData.size();
}

bool Packet::dataLeft() const
{
        return mReadPos >= mData.size();
}

Packet::operator bool() const
{
        return mIsValid;
}

Packet& Packet::operator>>(bool& data)
{
        Uint8 value;
        if (*this >> value)
        {
                data = (value != 0);
        }

        return *this;
}

Packet& Packet::operator>>(Int8& data)
{
        if (checkSize(sizeof(data)))
        {
                data = *reinterpret_cast<const Int8*>(&mData[mReadPos]);
                mReadPos += sizeof(data);
        }

        return *this;
}

Packet& Packet::operator>>(Uint8& data)
{
        if (checkSize(sizeof(data)))
        {
                data = *reinterpret_cast<const Uint8*>(&mData[mReadPos]);
                mReadPos += sizeof(data);
        }

        return *this;
}

Packet& Packet::operator>>(Int16& data)
{
        if (checkSize(sizeof(data)))
        {
                data = ntohs(*reinterpret_cast<const Int16*>(&mData[mReadPos]));
                mReadPos += sizeof(data);
        }

        return *this;
}

Packet& Packet::operator>>(Uint16& data)
{
        if (checkSize(sizeof(data)))
        {
                data = ntohs(*reinterpret_cast<const Uint16*>(&mData[mReadPos]));
                mReadPos += sizeof(data);
        }

        return *this;
}

Packet& Packet::operator>>(Int32& data)
{
        if (checkSize(sizeof(data)))
        {
                data = ntohl(*reinterpret_cast<const Int32*>(&mData[mReadPos]));
                mReadPos += sizeof(data);
        }

        return *this;
}

Packet& Packet::operator>>(Uint32& data)
{
        if (checkSize(sizeof(data)))
        {
                data = ntohl(*reinterpret_cast<const Uint32*>(&mData[mReadPos]));
                mReadPos += sizeof(data);
        }

        return *this;
}

Packet& Packet::operator>>(float& data)
{
        if (checkSize(sizeof(data)))
        {
                data = *reinterpret_cast<const float*>(&mData[mReadPos]);
                mReadPos += sizeof(data);
        }

        return *this;
}

Packet& Packet::operator>>(double& data)
{
        if (checkSize(sizeof(data)))
        {
                data = *reinterpret_cast<const double*>(&mData[mReadPos]);
                mReadPos += sizeof(data);
        }

        return *this;
}

Packet& Packet::operator>>(char* data)
{
        // Extract the string length
        Uint32 length = 0;
        *this >> length;

        if ((length > 0) && checkSize(length))
        {
                std::memcpy(data, &mData[mReadPos], length);
                data[length] = '\0';

                mReadPos += length;
        }

        return *this;
}

Packet& Packet::operator>>(std::string& data)
{
        // Extract the string length
        Uint32 length = 0;
        *this >> length;

        data.clear();
        if ((length > 0) && checkSize(length))
        {
                data.assign(&mData[mReadPos], length);
                mReadPos += length;
        }

        return *this;
}

Packet& Packet::operator<<(bool data)
{
        *this << static_cast<Uint8>(data);
        return *this;
}

Packet& Packet::operator<<(Int8 data)
{
        append(&data, sizeof(data));
        return *this;
}

Packet& Packet::operator<<(Uint8 data)
{
        append(&data, sizeof(data));
        return *this;
}

Packet& Packet::operator<<(Int16 data)
{
        Int16 toWrite = htons(data);
        append(&toWrite, sizeof(toWrite));
        return *this;
}

Packet& Packet::operator<<(Uint16 data)
{
        Uint16 toWrite = htons(data);
        append(&toWrite, sizeof(toWrite));
        return *this;
}

Packet& Packet::operator<<(Int32 data)
{
        Int32 toWrite = htonl(data);
        append(&toWrite, sizeof(toWrite));
        return *this;
}

Packet& Packet::operator<<(Uint32 data)
{
        Uint32 toWrite = htonl(data);
        append(&toWrite, sizeof(toWrite));
        return *this;
}

Packet& Packet::operator<<(float data)
{
        append(&data, sizeof(data));
        return *this;
}

Packet& Packet::operator<<(double data)
{
        append(&data, sizeof(data));
        return *this;
}

Packet& Packet::operator<<(const char* data)
{
        // Insert the string length
        Uint32 length = static_cast<Uint32>(std::strlen(data));
        *this << length;

        append(data, length * sizeof(char));
        return *this;
}

Packet& Packet::operator<<(const std::string& data)
{
        // Insert the string length
        Uint32 length = static_cast<Uint32>(data.size());
        *this << length;

        if (length > 0)
        {
                append(data.c_str(), length * sizeof(std::string::value_type));
        }

        return *this;
}

bool Packet::checkSize(std::size_t size)
{
        mIsValid = mIsValid && (mReadPos + size <= mData.size());

        return mIsValid;
}

ENetPacket* toENetPacket(const Packet& packet)
{
        Uint32 enetFlags = 0;
        if (packet.flag == Packet::Flag::Reliable)
        {
                enetFlags |= ENET_PACKET_FLAG_RELIABLE;
        }
        else if (packet.flag == Packet::Flag::Unreliable)
        {
                enetFlags |= ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT;
        }
        else if (packet.flag == Packet::Flag::Unsequenced)
        {
                enetFlags |= ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT
                        | ENET_PACKET_FLAG_UNSEQUENCED;
        }

        return enet_packet_create(packet.getData(), packet.getDataSize(),
                        enetFlags);
}
