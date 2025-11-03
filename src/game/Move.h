/**
 * @file Move.h
 * @brief Chess move representation
 */
#pragma once

#include "MoveType.h"
#include "core/PieceType.h"
#include "core/Position.h"
#include <optional>
#include <string>

namespace game {
/**
 * @brief Represents a chess move with necessary information
 *
 * Move stores starting position, destination, piece type, and move type
 * (normal, capture, castle, etc.). Check and checkmate flags are set
 * after move validation. Promotion piece is stored for pawn promotions.
 *
 */
class Move {
private:
  core::Position m_from;
  core::Position m_to;
  core::PieceType m_pieceType;
  MoveType m_type;
  // Move outcome flags
  bool m_bIsCheck;
  bool m_bIsCheckmate;
  // Special for pawn
  std::optional<core::PieceType> m_promotionPiece;

public:
  // Basic constructor (type defaults to NORMAL)
  Move(core::Position from, core::Position to, core::PieceType pieceType);
  // Move type constructor
  Move(core::Position from, core::Position to, core::PieceType pieceType,
       MoveType type);
  // Promotion constructor
  Move(core::Position from, core::Position to, core::PieceType pieceType,
       MoveType type, core::PieceType promotionPiece);

  // Getters
  core::Position getFrom() const;
  core::Position getTo() const;
  core::PieceType getPieceType() const;
  MoveType getType() const;
  std::optional<core::PieceType> getPromotionPiece() const;
  bool isCapture() const;
  bool isCastling() const;
  bool isEnPassant() const;
  bool isPromotion() const;
  bool isCheck() const;
  bool isCheckmate() const;

  // Setters
  void setType(MoveType type);
  void setCapture(bool capture);
  void setCastling(bool castling);
  void setEnPassant(bool enPassant);
  void setPromotion(core::PieceType promotionPiece);
  void setCheck(bool check);
  void setCheckmate(bool checkmate);

  // Notation getter
  std::string toAlgebraic() const;
};
} // namespace game
