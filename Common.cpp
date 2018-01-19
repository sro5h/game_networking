#include "Common.hpp"

#include "Event.hpp"

#include <iostream>

void logEvent(const Event& event)
{
        switch (event.type)
        {
                case Event::Type::Receive:
                {
                        std::cout << "Receive";
                } break;

                case Event::Type::Connect:
                {
                        std::cout << "Connect";
                } break;

                case Event::Type::Disconnect:
                {
                        std::cout << "Disconnect";
                } break;
        }

        std::cout << " from peer " << event.peer.id << std::endl;
}
