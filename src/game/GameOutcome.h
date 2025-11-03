/**
 * @file GameOutcome.h
 * @brief Enumeration class for game outcomes
 */
#pragma once

namespace game {
/**
 * @brief Enumerator class for game outcomes
 *
 * Game outcomes may be an active game or end
 * in a victory or a draw
 */
class GameOutcome {
public:
  enum Value {
    IN_PROGRESS,               // Active game
    CHECKMATE_WHITE_WINS,      // White wins
    CHECKMATE_BLACK_WINS,      // Black wins
    STALEMATE,                 // Draw - no legal moves, not in check
    DRAW_FIFTY_MOVE,           // Draw - 50 move rule
    DRAW_INSUFFICIENT_MATERIAL // Draw - can't mate
  };
  GameOutcome() = default;
  constexpr GameOutcome(Value value) : m_value(value) {}

  // Allow switch statements and comparisons
  constexpr operator Value() const { return m_value; }
  // prevent usage: if(gameStatus)
  explicit operator bool() = delete;

private:
  Value m_value;
};
} // namespace game
