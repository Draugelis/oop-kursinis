#include "bitboards/AttackTables.h"
#include "ui/controllers/ChessGameController.h"
#include "ui/windows/GameWindow.h"
#include "ui/windows/MainMenuWindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  // Initialize attack tables before game starts
  bitboards::AttackTables::initialize();

  // Create windows and controller
  MainMenuWindow *mainMenu = new MainMenuWindow();
  GameWindow *gameWindow = new GameWindow();
  ChessGameController *controller = new ChessGameController(gameWindow);

  // Connect game window back to main menu and vice-versa
  QObject::connect(mainMenu, &MainMenuWindow::startGameClicked, [&]() {
    mainMenu->hide();
    controller->startNewGame();
    gameWindow->show();
  });

  QObject::connect(gameWindow, &GameWindow::menuClicked, [&]() {
    gameWindow->hide();
    mainMenu->show();
  });

  QObject::connect(mainMenu, &MainMenuWindow::quitClicked, &app,
                   &QApplication::quit);

  mainMenu->show();

  return app.exec();
}