#pragma once

#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class MainMenuWindow : public QMainWindow {
  Q_OBJECT

private:
  // Main layout
  QVBoxLayout *m_pMainLayout;
  // Central container
  QWidget *m_pCentralWidget;

  // Game title label
  QLabel *m_pTitleLabel;
  // Start game button
  QPushButton *m_pStartButton;
  // Quit game button
  QPushButton *m_pQuitButton;

  // Setup UI components 
  void setupUI();
  // Apply button styling
  void applyButtonStyle(QPushButton *button);

public:
  explicit MainMenuWindow(QWidget *parent = nullptr);

signals:
  void startGameClicked();
  void quitClicked();
};