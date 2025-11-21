#include "Board.h"
#include "pieces/PieceFactory.h"
#include "core/Logging.h" 

namespace game {

/**
 * @brief Get a piece at the given position
 *
 * @param pos Position to check
 * @return std::unique_ptr<pieces::Piece>
 */
std::unique_ptr<pieces::Piece> Board::getPieceAt(core::Position pos) const {
  // Check if the position is even occupied
  if (isEmpty(pos)) {
    return nullptr;
  }

  // Check which color occupies the position
  core::Color color =
      m_bitboards.getColorOccupancy(core::Color::WHITE).isSet(pos)
          ? core::Color::WHITE
          : core::Color::BLACK;

  core::PieceType pieceType;
  // Iterate through all piece types
  for (auto type : core::PieceType::allTypes()) {
    // Check if this type occupies a tile
    if (m_bitboards.getPieceBitBoard(color, type).isSet(pos)) {
      pieceType = type;
      break; // no point to iterate further
    }
  }

  // construct a piece to return
  return pieces::PieceFactory::createPiece(color, pieceType);
}

/**
 * @brief Check if a given position is unoccupied
 *
 * @param pos Position to check
 * @return true If position is empty
 * @return false If position is occupied
 */
bool Board::isEmpty(core::Position pos) const {
  return !(m_bitboards.getAllOccupancy().isSet(pos));
}

/**
 * @brief Check if a given position is occupied by a color
 *
 * @param pos Position to check
 * @param color Color to check
 * @return true If color occupies the position
 * @return false If color doesn't occupy the position
 */
bool Board::isOccupiedBy(core::Position pos, core::Color color) const {
  return m_bitboards.getColorOccupancy(color).isSet(pos);
}

/**
 * @brief Place a piece at the position
 *
 * @param pos Where to place the piece
 * @param type What piece to place
 * @param color Which color to place
 */
void Board::placePiece(core::Position pos, core::PieceType type,
                       core::Color color) {
  // pass-through method to bitboards
  m_bitboards.setPiece(pos, color, type);
}

/**
 * @brief Place a piece at the position
 *
 * @param pos Where to place the piece
 * @param piece Which piece to place
 */
void Board::placePiece(core::Position pos, pieces::Piece &piece) {
  m_bitboards.setPiece(pos, piece.getColor(), piece.getType());
}

/**
 * @brief Remove a piece from a position
 *
 * @param pos Target position
 */
void Board::removePiece(core::Position pos) {
  // Get occupying piece
  auto piece = getPieceAt(pos);
  if (!piece) {
    qCWarning(boardDebug) << "removePiece: No piece at" 
                          << QString::fromStdString(pos.toString());
    return; // Nothing to remove
  }

  // Remove piece from bitboards
  m_bitboards.clearPiece(pos, piece->getColor(), piece->getType());
}

/**
 * @brief Move a piece from a given position to a new one
 *
 * @param from Starting position
 * @param to Destination position
 */
void Board::movePiece(core::Position from, core::Position to) {
  // Get piece at starting position
  auto piece = getPieceAt(from);
  if (!piece) {
    qCWarning(boardDebug) << "movePiece: No piece at" 
                          << QString::fromStdString(from.toString());
    return; // Nothing to move
  }

  // Remove any destination pieces before moving
  if (!isEmpty(to)) {
    removePiece(to);
  }

  // Execute piece move
  m_bitboards.movePiece(from, to, piece->getColor(), piece->getType());
}

} // namespace game