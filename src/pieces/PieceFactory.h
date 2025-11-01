#pragma once

#include "Piece.h"
#include "core/Color.h"
#include "core/PieceType.h"
#include <memory> // for unique_ptr and make_unique

namespace pieces {
/**
 * @brief Factory class for creating Piece objects
 *
 * Factory pattern for creating Piece instances based
 * on a given Color and PieceType.
 */
class PieceFactory {
public:
  static std::unique_ptr<Piece> createPiece(core::Color color,
                                            core::PieceType type);
};
} // namespace pieces