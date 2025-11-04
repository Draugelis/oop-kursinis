#include "Color.h"

namespace core {
const Color Color::opposite() const {
  return (m_value == WHITE) ? BLACK : WHITE;
}

const std::string Color::toString() const {
  return (m_value == WHITE) ? "White" : "Black";
}

const char Color::toLetter() const { return (m_value == WHITE) ? 'w' : 'b'; }
} // namespace core