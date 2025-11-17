#pragma once

#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>

class GameControlsWidget : public QWidget {
  Q_OBJECT

private:
  // Base horizontal layour
  QHBoxLayout *m_pLayout;
  // New game button
  QPushButton *m_pNewGameButton;
  // Back to menu button
  QPushButton *m_pMenuButton;

  // Setup the UI components
  void setupUI();
  // Apply button styling
  void applyButtonStyle(QPushButton *button);

public:
  explicit GameControlsWidget(QWidget *parent = nullptr);

  // Recommended size
  QSize sizeHint() const override;
  // Recommended minimum size
  QSize minimumSizeHint() const override;

signals:
  // New game button clicked
  void newGameClicked();
  // Back to menu button clicked
  void menuClicked();
};