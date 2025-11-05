#include "PieceType.h"
#include <stdexcept> // for invalid_argument exception

namespace core {
/**
 * @brief Get a string representation of the piece type
 * 
 * @return const std::string 
 */
const std::string PieceType::toString() const {
  switch (m_value) {
  case PAWN:
    return "Pawn";
  case KNIGHT:
    return "Knight";
  case BISHOP:
    return "Bishop";
  case ROOK:
    return "Rook";
  case QUEEN:
    return "Queen";
  case KING:
    return "King";
  default:
    return "Unknown";
  }
}

/**
 * @brief Get a letter associated with a piece type
 * 
 * @return char 
 */
const char PieceType::getLetter() const {
  switch (m_value) {
  case PAWN:
    return 'P';
  case KNIGHT:
    return 'N';
  case BISHOP:
    return 'B';
  case ROOK:
    return 'R';
  case QUEEN:
    return 'Q';
  case KING:
    return 'K';
  default:
    return '?';
  }
}

/**
 * @brief Translate piece letter into a PieceType
 *
 * Why did I add this? is it even used?
 * TODO: Evaluate whether this method is really needed and remove if not.
 *
 * @param c Piece letter
 * @return PieceType
 */
PieceType PieceType::fromChar(char c) {
  switch (std::tolower(c)) {
  case 'p':
    return PAWN;
  case 'n':
    return KNIGHT;
  case 'b':
    return BISHOP;
  case 'r':
    return ROOK;
  case 'q':
    return QUEEN;
  case 'k':
    return KING;
  default:
    throw std::invalid_argument("invalid piece character: " +
                                std::string(1, c));
  }
}

/**
 * @brief Return all PieceTypes for iteration
 *
 * Naively assuming that ordering will not change in the main enum nor here. I
 * could, and probably should, do an iterator pattern but this is good enough
 * for my use case (watch this haunt me later)
 *
 * @return std::vector<PieceType>
 */
std::vector<PieceType> PieceType::allTypes() {
  return {PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING};
}
} // namespace core