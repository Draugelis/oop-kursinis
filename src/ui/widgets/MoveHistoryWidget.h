#pragma once

#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QString>
#include <vector>


class MoveHistoryWidget : public QWidget {
  Q_OBJECT;

private:
  QVBoxLayout *m_pLayout;
  QTableWidget *m_ptableWidget;
  std::vector<QString> m_moves;

  void setupUI();
  void rebuildTable();
  void scrollToBottom();

public:
  explicit MoveHistoryWidget(QWidget *parent = nullptr);

  void addMove(const QString &move);
  void setMoves(const std::vector<QString> &moves);
  void clearHistory();

  QSize sizeHint() const override;
  QSize minimumSizeHint() const override;
};