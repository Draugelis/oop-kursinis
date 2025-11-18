#pragma once

#include <QHeaderView>
#include <QString>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <vector>

class MoveHistoryWidget : public QWidget {
  Q_OBJECT

private:
  // Base vertical layout
  QVBoxLayout *m_pLayout;
  // Table widget for moves
  QTableWidget *m_pTableWidget;
  // Move vector
  std::vector<QString> m_moves;

  // Setup UI components
  void setupUI();
  // Rebuild table from move vector
  void rebuildTable();
  // Scroll to bottom of table to show latest move
  void scrollToBottom();

public:
  explicit MoveHistoryWidget(QWidget *parent = nullptr);

  // Add a move to the history
  void addMove(const QString &move);
  // Set all moves
  void setMoves(const std::vector<QString> &moves);
  // Clear whole move history
  void clearHistory();

  // New game button clicked
  void newGameClicked();
  // Back to menu button clicked
  void menuClicked();

  // Recommended size
  QSize sizeHint() const override;
  // Recommended minimum size
  QSize minimumSizeHint() const override;
};