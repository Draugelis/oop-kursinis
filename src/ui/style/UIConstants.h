/**
 * @file UIConstants.h
 * @brief UI dimensions and sizing constants
 */
#pragma once

namespace UIConstants {
// Game window sizing
constexpr int GAME_WINDOW_WIDTH = 1024; // 4x3 scale
constexpr int GAME_WINDOW_HEIGHT = 768; // 4x3 scale

// Sizing ratios in the game window
constexpr double STATUS_BAR_HEIGHT_RATIO = 0.05;
constexpr double BOARD_WIDTH_RATIO = 0.70;
constexpr double SIDEBAR_WIDTH_RATIO = 0.30;
constexpr double MOVE_HISTORY_HEIGHT_RATIO = 0.90;
constexpr double GAME_CONTROLS_HEIGHT_RATIO = 0.10;

// Main menu sizing
constexpr int MAIN_MENU_WIDTH = 640;  // 4x3 scale
constexpr int MAIN_MENU_HEIGHT = 480; // 4x3 scale
constexpr int MAIN_MENU_MARGIN = 50;
constexpr int MAIN_MENU_SPACING = 30;
constexpr int MAIN_MENU_TITLE_SPACING = 50;
constexpr int MAIN_MENU_BUTTON_MIN_WIDTH = 240;
constexpr int MAIN_MENU_BUTTON_MIN_HEIGHT = 60;
constexpr int MAIN_MENU_BUTTON_PADDING = 15;

// Square sizing
constexpr int SQUARE_MIN_SIZE = 40;
constexpr int SQUARE_PREFERRED_SIZE = 80;
constexpr int PIECE_MARGIN = 5;
constexpr int SQUARE_INDICATOR_MARGIN = 2;
constexpr int SQUARE_INDICATOR_BORDER_WIDTH = 4;

// Status bar
constexpr int STATUS_BAR_SIDE_MARGIN = 10;
constexpr int STATUS_BAR_VERTICAL_MARGIN = 5;
constexpr int STATUS_BAR_MIN_WIDTH = 400;
constexpr int STATUS_BAR_FALLBACK_WIDTH = GAME_WINDOW_WIDTH;

// Move history
constexpr int MOVE_HISTORY_MARGIN = 5;
constexpr int MOVE_HISTORY_MOVE_NUMBER_WIDTH = 40;
constexpr int MOVE_HISTORY_MIN_WIDTH = 150;
constexpr int MOVE_HISTORY_MIN_HEIGHT = 200;
constexpr int MOVE_HISTORY_FALLBACK_WIDTH = 300;
constexpr int MOVE_HISTORY_FALLBACK_HEIGHT = 600;

// Game controls
constexpr int GAME_CONTROLS_MARGIN = 10;
constexpr int GAME_CONTROLS_SPACING = 20;
constexpr int GAME_CONTROLS_BUTTON_MIN_WIDTH = 120;
constexpr int GAME_CONTROLS_BUTTON_MIN_HEIGHT = 40;
constexpr int GAME_CONTROLS_BUTTON_PADDING = 5;
constexpr int GAME_CONTROLS_MIN_WIDTH = 280;
constexpr int GAME_CONTROLS_MIN_HEIGHT = 60;
constexpr int GAME_CONTROLS_FALLBACK_WIDTH = 300;
constexpr int GAME_CONTROLS_FALLBACK_HEIGHT = 80;

// Board container
constexpr int BOARD_CONTAINER_MARGIN = 10;

// Promotion dialog
constexpr int PROMOTION_DIALOG_WIDTH = 400;
constexpr int PROMOTION_DIALOG_HEIGHT = 350;
constexpr int PROMOTION_BUTTON_SIZE = 150;
constexpr int PROMOTION_ICON_SIZE = 100;
constexpr int PROMOTION_GRID_SPACING = 10;

// Typography
constexpr const char* DEFAULT_TYPEFACE = "Press Start 2P";
constexpr int FONT_SIZE_SMALL = 10;
constexpr int FONT_SIZE_STANDARD = 12;
constexpr int FONT_SIZE_MEDIUM = 14;
constexpr int FONT_SIZE_LARGE = 16;
constexpr int FONT_SIZE_TITLE = 24;

// Borders
constexpr int BORDER_THIN = 2;
constexpr int BORDER_MEDIUM = 3;
constexpr int BORDER_RADIUS_SMALL = 5;
constexpr int BORDER_RADIUS_MEDIUM = 10;

// Asset paths
constexpr const char* PIECE_IMG_PATH_TEMPLATE = ":/assets/pieces/%1_%2.png";
} // namespace UIConstants