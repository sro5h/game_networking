#ifndef PACKET_HPP
#define PACKET_HPP

#include "Types.hpp"

#include <string>
#include <vector>

class Packet
{
public:
        enum class Flag : Uint16;

public:
        /**
         * Creates a Packet with the specified flag, defaults to
         * Flag::Unreliable.
         */
        Packet(Flag flag = Flag::Unreliable);

        /**
         * Appends data of size size to the Packet.
         * @param data The pointer to the data to append
         * @param size The size of the data
         */
        void append(const void* data, std::size_t size);

        /**
         * Resets the packet, clearing its data and read position.
         */
        void clear();

        /**
         * Returns a pointer to the data associated with the Packet.
         * @return A pointer to the data
         */
        const void* getData() const;

        /**
         * Returns the size of the data associated with the Packet.
         * @return The size of the data
         */
        std::size_t getDataSize() const;

        /**
         * Returns whether there is data left to read.
         * @return True whether data can be read
         */
        bool dataLeft() const;

public:
        /**
         * Returns whether the Packet is in a valid state.
         * @return True if the Packet is valid
         */
        explicit operator bool() const;

        /**
         * Overloads for operator>> to read from the Packet.
         * Automatically converts the byte order from Network to Host.
         */
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

        /**
         * Overloads for operator<< to append data to the Packet.
         * Automatically converts the byte order from Host to Network.
         */
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
        /**
         * The flag to use when sending the Packet.
         * Reliable means the Packet will get resent until it is acknoledged.
         * Unreliable means the Packet will get sent once.
         * Unsequenced means the order in which the Packet was sent will be
         * ignored.
         */
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

        /**
         * Checks if the data to read will not exceed the data size.
         * @param size The size of the data to read
         * @return True if the data of size size can be read
         */
        bool checkSize(std::size_t size);

        std::vector<char> mData;
        std::size_t mReadPos;
        bool mIsValid;
};

/**
 * A helper function to convert a Packet to an ENetPacket.
 * Creates an ENetPacket that needs to be destroyed with
 * enet_packet_destroy later.
 * @param packet The Packet to convert from
 * @return A pointer to the converted ENetPacket
 */
ENetPacket* toENetPacket(const Packet& packet);

#endif // PACKET_HPP
