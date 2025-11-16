#pragma once

#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class MainMenuWindow : public QMainWindow {
  Q_OBJECT

private:
  QVBoxLayout *m_pMainLayout;
  QWidget *m_pCentralWidget;

  QLabel *m_pTitleLabel;
  QPushButton *m_pStartButton;
  QPushButton *m_pQuitButton;

  void setupUI();
  void applyButtonStyle(QPushButton *button);

public:
  explicit MainMenuWindow(QWidget *parent = nullptr);

signals:
  void startGameClicked();
  void quitClicked();
};