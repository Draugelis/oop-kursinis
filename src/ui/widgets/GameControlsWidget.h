#pragma once

#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>

class GameControlsWidget : public QWidget {
  Q_OBJECT;

private:
  QHBoxLayout *m_pLayout;
  QPushButton *m_pNewGameButton;
  QPushButton *m_pMenuButton;

  void setupUI();
  void applyButtonStyle(QPushButton *button);

public:
  explicit GameControlsWidget(QWidget *parent = nullptr);

  QSize sizeHint() const override;
  QSize minimumSizeHint() const override;

signals:
  void newGameClicked();
  void menuClicked();
};