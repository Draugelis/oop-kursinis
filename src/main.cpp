#include "bitboards/AttackTables.h"
#include "core/Logging.h"
#include "ui/controllers/ChessGameController.h"
#include "ui/windows/GameWindow.h"
#include "ui/windows/MainMenuWindow.h"
#include <QApplication>
#include <QCommandLineParser>
#include <QDir>
#include <QDirIterator>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  // Parse command line
  QCommandLineParser parser;
  parser.setApplicationDescription("Chess Game");
  parser.addHelpOption();

  QCommandLineOption debugOption(QStringList() << "d" << "debug",
                                 "Enable debug output");
  parser.addOption(debugOption);
  parser.process(app);

  // Enable debug logging if flag is set
  if (parser.isSet(debugOption)) {
    QLoggingCategory::setFilterRules(
        "qt.*.debug=false\n" // Disable internal Qt debug
        "ui.debug=true\n"
        "game.debug=true\n"
        "move.debug=true\n"
        "board.debug=true\n"
        "resources.debug=false\n"
        "default.debug=true" // Allow uncategorized qDebug
    );

    Logger::FunctionScope logScope;
    Logger::debug(gameDebug(), "Debug mode enabled");
  }

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