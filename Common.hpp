#ifndef COMMON_HPP
#define COMMON_HPP

#include <type_traits>

class Event;

template<typename Enum>
constexpr auto toIntegral(Enum e) -> typename std::underlying_type<Enum>::type
{
        return static_cast<typename std::underlying_type<Enum>::type>(e);
}

void logEvent(const Event& event);

#endif // COMMON_HPP
