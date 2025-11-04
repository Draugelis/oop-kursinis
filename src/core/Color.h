/**
 * @file Color.h
 *
 * @brief Enumeration class for chess piece colors
 *
 */
#pragma once

#include <string>

namespace core {
/**
 * @brief Enumerator class for Chess piece colors
 *
 * Color class implements enum for chess piece colors
 * and contains supporting methods to fetch color string
 * name or letter
 *
 * @note Refered to https://stackoverflow.com/a/53284026 for implementation
 */
class Color {
public:
  enum Value { WHITE, BLACK };

  Color() = default;
  constexpr Color(Value value) : m_value(value) {}

  // Allows switch statements and comparisons
  constexpr operator Value() const { return m_value; }
  // prevent usage: if(color)
  explicit operator bool() = delete;

  const Color opposite() const;
  const std::string toString() const;
  const char toLetter() const;

private:
  Value m_value;
};

} // namespace core