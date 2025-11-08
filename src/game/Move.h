/**
 * @file Move.h
 * @brief Chess move representation
 */
#pragma once

#include "MoveType.h"
#include "core/Color.h"
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
  // Starting position
  core::Position m_from;
  // Destination position
  core::Position m_to;
  // Piece type that moves
  core::PieceType m_pieceType;
  // Move type (normal, capture, castle, etc.)
  MoveType m_type;
  // Color that moved
  core::Color m_color;
  // Whether the move result in check
  bool m_bIsCheck;
  // Whether the move result in checkmate
  bool m_bIsCheckmate;
  // Pawn promotion piece
  std::optional<core::PieceType> m_promotionPiece;

public:
  // Basic constructor (type defaults to NORMAL)
  Move(core::Position from, core::Position to, core::PieceType pieceType,
       core::Color color);
  // Move type constructor
  Move(core::Position from, core::Position to, core::PieceType pieceType,
       core::Color color, MoveType type);
  // Promotion constructor
  Move(core::Position from, core::Position to, core::PieceType pieceType,
       core::Color color, MoveType type, core::PieceType promotionPiece);

  // Get starting position
  core::Position getFrom() const;
  // Get destination position
  core::Position getTo() const;
  // Get piece type that moves
  core::PieceType getPieceType() const;
  // Get move type
  MoveType getType() const;
  // Get pawn promotion type
  std::optional<core::PieceType> getPromotionPiece() const;
  // Check if move is capture type
  bool isCapture() const;
  // Check if move is castling type
  bool isCastling() const;
  // Check if move is en passant type
  bool isEnPassant() const;
  // Check if move is promotion type
  bool isPromotion() const;
  // Check if move is check type
  bool isCheck() const;
  // Check if move is checkmate type
  bool isCheckmate() const;

  // Set move type
  void setType(MoveType type);
  // Set capture move type
  void setCapture();
  // Set castling move type
  void setCastling(bool kingside);
  // Set en passant move type
  void setEnPassant();
  // Set promotion move type and piece
  void setPromotion(core::PieceType promotionPiece, bool capture = false);
  // Set move as resulting in check
  void setCheck();
  // Set move as resulting in checkmate
  void setCheckmate();

  // Convert move to algebraic notation
  std::string toAlgebraic() const;
};
} // namespace game
