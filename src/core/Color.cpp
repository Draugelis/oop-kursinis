#include "Color.h"

const std::string Core::Color::toString() const {
    return (m_value == WHITE) ? "White" : "Black";
}

const char Core::Color::toLetter() const {
    return (m_value == WHITE) ? 'w' : 'b';
}