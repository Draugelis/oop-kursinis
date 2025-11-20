/**
 * @file ChessGameController.cpp
 * @brief Chess Game Controller implementation
 */

#include "ChessGameController.h"
#include "ui/widgets/PromotionDialog.h"
#include <QMessageBox>

/**
 * @brief Construct a new Chess Game Controller object
 *
 * @param gameWindow Pointer to game window
 * @param parent Parent QObject
 */
ChessGameController::ChessGameController(GameWindow *gameWindow,
                                         QObject *parent)
    : QObject(parent), m_pGameWindow(gameWindow),
      m_pGameState(std::make_unique<game::GameState>()),
      m_selectedPosition(0, 0), m_bPieceSelected(false) {

  // Connect UI signals to slots
  connect(m_pGameWindow, &GameWindow::squareClicked, this,
          &ChessGameController::handleSquareClick);
  connect(m_pGameWindow, &GameWindow::newGameClicked, this,
          &ChessGameController::handleNewGame);

  // Initialize display
  updateBoardDisplay();
  updateStatusDisplay();
  updateMoveHistoryDisplay();
}

/**
 * @brief Initialize new game
 *
 */
void ChessGameController::startNewGame() {
  m_pGameState->reset();
  m_bPieceSelected = false;

  // Update UI
  m_pGameWindow->getBoardWidget()->clearSelection();
  m_pGameWindow->getBoardWidget()->clearLegalMoves();
  m_pGameWindow->getMoveHistoryWidget()->clearHistory();

  updateBoardDisplay();
  updateStatusDisplay();
  updateMoveHistoryDisplay();
}

/**
 * @brief Initialize game from FEN notation
 *
 * @param fen FEN string
 */
void ChessGameController::startNewGame(const QString &fen) {
  m_pGameState->reset(fen.toStdString());
  m_bPieceSelected = false;

  // Update UI
  m_pGameWindow->getBoardWidget()->clearSelection();
  m_pGameWindow->getBoardWidget()->clearLegalMoves();
  m_pGameWindow->getMoveHistoryWidget()->clearHistory();

  updateBoardDisplay();
  updateStatusDisplay();
  updateMoveHistoryDisplay();
}

/**
 * @brief Handle square click from board widget
 *
 * @param row Clicked square row
 * @param col Clicked square col
 */
void ChessGameController::handleSquareClick(int row, int col) {
  // Game must be in progress
  if (m_pGameState->getOutcome() != game::GameOutcome::IN_PROGRESS) {
    return;
  }

  core::Position clickedPos(uiRowToEngineRank(row), col);
  game::Board &board = m_pGameState->getBoard();

  // No piece selected yet
  if (!m_bPieceSelected) {
    // Get piece at clicked position
    auto piece = board.getPieceAt(clickedPos);

    // Must click on the same color piece
    if (!piece || piece->getColor() != m_pGameState->getSideToMove()) {
      return;
    }

    // Select piece
    m_selectedPosition = clickedPos;
    m_bPieceSelected = true;

    // Update UI
    m_pGameWindow->getBoardWidget()->setSelectedSquare(row, col);
    m_pGameWindow->getBoardWidget()->setLegalMoveSquares(
        getLegalMovesForSelected());

    return;
  }

  // Deselect if the same square is selected
  if (clickedPos == m_selectedPosition) {
    m_bPieceSelected = false;
    m_pGameWindow->getBoardWidget()->clearSelection();
    m_pGameWindow->getBoardWidget()->clearLegalMoves();
    return;
  }

  // Find matching move from legal moves
  std::vector<game::Move> legalMoves =
      m_pGameState->getLegalMovesFrom(m_selectedPosition);
  game::Move *matchedMove = nullptr;
  for (auto &move : legalMoves) {
    if (move.getTo() == clickedPos) {
      matchedMove = &move;
      break;
    }
  }

  // Try reselecting for invalid move
  if (!matchedMove) {
    auto piece = board.getPieceAt(clickedPos);

    // Switch selection for own piece
    if (piece && piece->getColor() == m_pGameState->getSideToMove()) {
      m_selectedPosition = clickedPos;
      m_pGameWindow->getBoardWidget()->setSelectedSquare(row, col);
      m_pGameWindow->getBoardWidget()->setLegalMoveSquares(
          getLegalMovesForSelected());
      return;
    }

    // Deselect for invalid move
    m_bPieceSelected = false;
    m_pGameWindow->getBoardWidget()->clearSelection();
    m_pGameWindow->getBoardWidget()->clearLegalMoves();
    return;
  }

  // Handle promotion
  if (matchedMove->isPromotion()) {
    if (!handlePromotion(*matchedMove)) {
      // Promotion cancelled
      m_bPieceSelected = false;
      m_pGameWindow->getBoardWidget()->clearSelection();
      m_pGameWindow->getBoardWidget()->clearLegalMoves();
      return;
    }
  }

  // Execute move
  bool success = m_pGameState->tryMove(*matchedMove);

  if (success) {
    // Reset selection
    m_bPieceSelected = false;
    m_pGameWindow->getBoardWidget()->clearSelection();
    m_pGameWindow->getBoardWidget()->clearLegalMoves();

    // Update displays
    updateBoardDisplay();
    updateStatusDisplay();
    updateMoveHistoryDisplay();

    // Check for game end
    game::GameOutcome outcome = m_pGameState->getOutcome();
    if (outcome != game::GameOutcome::IN_PROGRESS) {
      QString message;
      switch (outcome) {
      case game::GameOutcome::CHECKMATE_WHITE_WINS:
        message = "Checkmate! White wins!";
        break;
      case game::GameOutcome::CHECKMATE_BLACK_WINS:
        message = "Checkmate! Black wins!";
        break;
      case game::GameOutcome::STALEMATE:
        message = "Stalemate! Draw.";
        break;
      case game::GameOutcome::DRAW_FIFTY_MOVE:
        message = "Draw by fifty-move rule.";
        break;
      case game::GameOutcome::DRAW_INSUFFICIENT_MATERIAL:
        message = "Draw by insufficient material.";
        break;
      default:
        break;
      }

      // Display game over message
      if (!message.isEmpty()) {
        QMessageBox::information(m_pGameWindow, "Game Over", message);
      }
    }
  }
}

/**
 * @brief Handle new game button click
 *
 */
void ChessGameController::handleNewGame() { startNewGame(); }

/**
 * @brief Update board display from game state
 *
 */
void ChessGameController::updateBoardDisplay() {
  std::vector<std::vector<QString>> piecePaths = convertBoardToPiecePaths();
  m_pGameWindow->getBoardWidget()->setPiecePositions(piecePaths);
}

/**
 * @brief Update status bar display
 *
 */
void ChessGameController::updateStatusDisplay() {
  // Update turn
  QString turn =
      QString::fromStdString(m_pGameState->getSideToMove().toString());
  m_pGameWindow->getStatusBarWidget()->setCurrentTurn(turn);

  // Update status
  QString status;
  game::GameOutcome outcome = m_pGameState->getOutcome();

  switch (outcome) {
  case game::GameOutcome::IN_PROGRESS:
    status = "In Progress";
    break;
  case game::GameOutcome::CHECKMATE_WHITE_WINS:
    status = "Checkmate - White Wins";
    break;
  case game::GameOutcome::CHECKMATE_BLACK_WINS:
    status = "Checkmate - Black Wins";
    break;
  case game::GameOutcome::STALEMATE:
    status = "Stalemate - Draw";
    break;
  case game::GameOutcome::DRAW_FIFTY_MOVE:
    status = "Draw - Fifty Move Rule";
    break;
  case game::GameOutcome::DRAW_INSUFFICIENT_MATERIAL:
    status = "Draw - Insufficient Material";
    break;
  }
  m_pGameWindow->getStatusBarWidget()->setGameStatus(status);
}

/**
 * @brief Update move history display
 *
 */
void ChessGameController::updateMoveHistoryDisplay() {
  const std::vector<game::Move> &moves = m_pGameState->getMoveHistory();

  std::vector<QString> moveStrings;
  for (const auto &move : moves) {
    moveStrings.push_back(moveToAlgebraic(move));
  }

  m_pGameWindow->getMoveHistoryWidget()->setMoves(moveStrings);
}

/**
 * @brief Covnert board state to piece SVG paths
 *
 * @return std::vector<std::vector<QString>> 8x8 grid of SVG paths
 */
std::vector<std::vector<QString>>
ChessGameController::convertBoardToPiecePaths() {
  std::vector<std::vector<QString>> paths(8,
                                          std::vector<QString>(8, QString()));

  game::Board &board = m_pGameState->getBoard();

  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      core::Position pos(uiRowToEngineRank(row), col);
      auto piece = board.getPieceAt(pos);

      if (piece) {
        paths[row][col] = getPieceSvgPath(piece->getType(), piece->getColor());
      }
    }
  }

  return paths;
}

/**
 * @brief Get legal moves for selected piece
 *
 * @return std::vector<std::vector<bool>> 8x8 grid of legal move flags
 */
std::vector<std::vector<bool>> ChessGameController::getLegalMovesForSelected() {
  std::vector<std::vector<bool>> legalMoves(8, std::vector<bool>(8, false));

  if (!m_bPieceSelected) {
    return legalMoves;
  }

  std::vector<game::Move> moves =
      m_pGameState->getLegalMovesFrom((m_selectedPosition));

  for (const auto &move : moves) {
    core::Position to = move.getTo();
    legalMoves[engineRankToUiRow(to.getRank())][to.getFile()] = true;
  }

  return legalMoves;
}

/**
 * @brief Convert piece type and color to SVG path
 *
 * @param type Piece type
 * @param color Piece color
 * @return QString SVG file path
 */
QString ChessGameController::getPieceSvgPath(core::PieceType type,
                                             core::Color color) const {
  QString colorPrefix = (color == core::Color::WHITE) ? "w" : "b";
  QString pieceName;

  switch (type) {
  case core::PieceType::PAWN:
    pieceName = "pawn";
    break;
  case core::PieceType::KNIGHT:
    pieceName = "knight";
    break;
  case core::PieceType::BISHOP:
    pieceName = "bishop";
    break;
  case core::PieceType::ROOK:
    pieceName = "rook";
    break;
  case core::PieceType::QUEEN:
    pieceName = "queen";
    break;
  case core::PieceType::KING:
    pieceName = "king";
    break;
  }

  return QString(":/pieces/%1_%2.svg").arg(colorPrefix).arg(pieceName);
}

/**
 * @brief Convert Move to algebraic notation
 *
 * @param move Move object
 * @return QString Algebraic notation
 */
QString ChessGameController::moveToAlgebraic(const game::Move &move) const {
  return QString::fromStdString(move.toAlgebraic());
}

/**
 * @brief Handle pawn promotion dialog
 *
 * @param move Move object to set promotion piece
 * @return true If promotion piece selected
 * @return false If user cancelled
 */
bool ChessGameController::handlePromotion(game::Move &move) {
  bool isWhite = (move.getColor() == core::Color::WHITE);

  PromotionDialog dialog(isWhite, m_pGameWindow);
  int result = dialog.exec();

  if (result == QDialog::Accepted) {
    QString selectedPiece = dialog.getSelectedPiece();

    core::PieceType promotionType;
    if (selectedPiece == "Queen") {
      promotionType = core::PieceType::QUEEN;
    } else if (selectedPiece == "Rook") {
      promotionType = core::PieceType::ROOK;
    } else if (selectedPiece == "Bishop") {
      promotionType = core::PieceType::BISHOP;
    } else if (selectedPiece == "Knight") {
      promotionType = core::PieceType::KNIGHT;
    } else {
      return false;
    }

    move.setPromotion(promotionType, move.isCapture());
    return true;
  }

  return false;
}

/**
 * @brief Convert UI row (0=top) to engine rank (0=bottom)
 *
 * @param row UI row (0-7, where 0 is rank 8)
 * @return int Engine rank (0-7, where 0 is rank 1)
 */
int ChessGameController::uiRowToEngineRank(int row) const { return 7 - row; }

/**
 * @brief Convert engine rank (0=bottom) to UI row (0=top)
 *
 * @param rank Engine rank (0-7, where 0 is rank 1)
 * @return int UI row (0-7, where 0 is rank 8)
 */
int ChessGameController::engineRankToUiRow(int rank) const { return 7 - rank; }