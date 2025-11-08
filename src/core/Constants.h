/**
 * @file Constants.h
 * @brief Constant values used across the chess game
 *
 */
#pragma once

namespace core {
// Board dimensions
constexpr int BOARD_SIZE = 8;
constexpr int TOTAL_SQUARES = BOARD_SIZE * BOARD_SIZE;
constexpr int NUM_FILES = BOARD_SIZE;
constexpr int NUM_RANKS = BOARD_SIZE;

// Bitboard bit offsets
constexpr int PAWN_PUSH_BIT_OFFSET = 8;

// Piece counts
constexpr int NUM_PIECE_TYPES = 6;
constexpr int MAX_PIECES_PER_COLOR = 16;

// Game rules
constexpr int MAX_HALFMOVE_CLOCK = 100;

// Rank indices (1-8)
constexpr int RANK_1 = 0;
constexpr int RANK_2 = 1;
constexpr int RANK_3 = 2;
constexpr int RANK_4 = 3;
constexpr int RANK_5 = 4;
constexpr int RANK_6 = 5;
constexpr int RANK_7 = 6;
constexpr int RANK_8 = 7;

// File indices (a-h)
constexpr int FILE_A = 0;
constexpr int FILE_B = 1;
constexpr int FILE_C = 2;
constexpr int FILE_D = 3;
constexpr int FILE_E = 4;
constexpr int FILE_F = 5;
constexpr int FILE_G = 6;
constexpr int FILE_H = 7;

// Position boundaries
constexpr int MIN_RANK = RANK_1;
constexpr int MAX_RANK = RANK_8;
constexpr int MIN_FILE = FILE_A;
constexpr int MAX_FILE = FILE_H;

// Default board FEN notation
constexpr char DEFAULT_BOARD_FEN[] =
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
} // namespace core