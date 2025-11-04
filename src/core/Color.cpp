#include "Color.h"

const core::Color core::Color::opposite() const {
    return (m_value == WHITE) ? BLACK : WHITE;
}

const std::string core::Color::toString() const {
    return (m_value == WHITE) ? "White" : "Black";
}

const char core::Color::toLetter() const {
    return (m_value == WHITE) ? 'w' : 'b';
}