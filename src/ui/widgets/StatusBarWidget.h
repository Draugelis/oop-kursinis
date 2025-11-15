#pragma once

#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>

class StatusBarWidget : public QWidget {
  Q_OBJECT;

private:
  QHBoxLayout *m_pLayout;
  QLabel *m_pTurnLabel;
  QLabel *m_pStatusLabel;

  void setupUI();
  void updateStatusColor(const QString &status);

public:
  explicit StatusBarWidget(QWidget *parent = nullptr);

  void setCurrentTurn(const QString &turn);
  void setGameStatus(const QString &status);

  QSize sizeHint() const override;
  QSize minimumSizeHint() const override;
};