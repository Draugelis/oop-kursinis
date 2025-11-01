#include "PieceType.h"
#include <stdexcept>  // for invalid_argument exception

const std::string Core::PieceType::toString() const {
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

char Core::PieceType::getLetter() const {
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

Core::PieceType Core::PieceType::fromChar(char c) {
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