#include "BitBoardManager.h"

/**
 * @brief Retrieves BitBoard for a piece type of a color
 *
 * @param color core::Color Piece color value for a piece
 * @param type core::PieceType Piece type value for a piece
 * @return bitboards::BitBoard
 */
bitboards::BitBoard
bitboards::BitBoardManager::getPieceBitBoard(core::Color color,
                                             core::PieceType type) const {
  int index = static_cast<int>(type);

  if (color == core::Color::WHITE) {
    return m_whitePieces[index];
  }
  return m_blackPieces[index];
}

/**
 * @brief Retrieves BitBoard for all pieces occupancy of all colors
 *
 * @param color core::Color Piece color value for a piece
 * @return bitboards::BitBoard
 */
bitboards::BitBoard
bitboards::BitBoardManager::getColorOccupancy(core::Color color) const {
  if (color == core::Color::WHITE) {
    return m_whiteOccupancy;
  }
  return m_blackOccupancy;
}

/**
 * @brief Retrieves BitBoard for all pieces occupancy of a color
 *
 * @return bitboards::BitBoard
 */
bitboards::BitBoard bitboards::BitBoardManager::getAllOccupancy() const {
  return m_whiteOccupancy | m_blackOccupancy;
}

/**
 * @brief Sets piece's position in a bitboard
 *
 * Sets piece's position in a bitboard for a given color and piece type
 *
 * @param pos core::Position piece's position
 * @param color core::Color piece's color
 * @param type core::PieceType piece's type
 */
void bitboards::BitBoardManager::setPiece(const core::Position &pos,
                                          core::Color color,
                                          core::PieceType type) {
  int index = static_cast<int>(type);

  if (color == core::Color::WHITE) {
    m_whitePieces[index].setBit(pos);
  } else {
    m_blackPieces[index].setBit(pos);
  }

  updateOccupancy();
}

/**
 * @brief Clears piece's position in a bitboard
 *
 * Clears piece's position in a bitboard for a given color and piece type
 *
 * @param pos core::Position piece's position
 * @param color core::Color piece's color
 * @param type core::PieceType piece's type
 */
void bitboards::BitBoardManager::clearPiece(const core::Position &pos,
                                            core::Color color,
                                            core::PieceType type) {
  int index = static_cast<int>(type);

  if (color == core::Color::WHITE) {
    m_whitePieces[index].clearBit(pos);
  } else {
    m_blackPieces[index].clearBit(pos);
  }

  updateOccupancy();
}

/**
 * @brief Moves piece to a new location
 *
 * @param from core::Position piece's starting position
 * @param to core::Position piece's target position
 * @param color core::Color piece's color
 * @param type core::PieceType piece's type
 */
void bitboards::BitBoardManager::movePiece(const core::Position &from,
                                           const core::Position &to,
                                           core::Color color,
                                           core::PieceType type) {
  clearPiece(from, color, type);
  setPiece(to, color, type);
}

/**
 * @brief Update occupancy bitboards
 *
 * Occupancy bitboards are reset and recreated after setting or clearing bits
 */
void bitboards::BitBoardManager::updateOccupancy() {
  // Reset occupancies
  m_whiteOccupancy = bitboards::BitBoard();
  m_blackOccupancy = bitboards::BitBoard();

  // Re-populate occupancy bitboards
  for (int i = 0; i < core::NUM_PIECE_TYPES; i++) {
    m_whiteOccupancy |= m_whitePieces[i];
    m_blackOccupancy |= m_blackPieces[i];
  }
}