#pragma once

#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>

/**
 * @brief Widget for game's status bar
 * 
 * Displays current move and game status
 */
class StatusBarWidget : public QWidget {
  // Qt Meta-Object Compiler
  // https://doc.qt.io/qt-6/qobject.html#Q_OBJECT
  Q_OBJECT 

private:
  // Horizontal layout for storing labels
  QHBoxLayout *m_pLayout;
  QLabel *m_pTurnLabel;
  QLabel *m_pStatusLabel;

  // Setup UI components and layout
  void setupUI();
  // Update status label color based on game state
  void updateStatusColor(const QString &status);

public:
  explicit StatusBarWidget(QWidget *parent = nullptr);

  // Set current turn text
  void setCurrentTurn(const QString &turn);
  // Set game status text and update color
  void setGameStatus(const QString &status);

  // Recommended status bar size hint
  QSize sizeHint() const override;
  // Recommended minimum status bar size hint
  QSize minimumSizeHint() const override;
};