#include "Color.h"

const std::string core::Color::toString() const {
    return (m_value == WHITE) ? "White" : "Black";
}

const char core::Color::toLetter() const {
    return (m_value == WHITE) ? 'w' : 'b';
}