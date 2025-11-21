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
        "qt.*.debug=false\n"   // Disable internal Qt debug
        "ui.debug=true\n"      // Enable game's ui category
        "game.debug=true\n"    // Enable game's game category
        "resources.debug=true" // Enable game's resources category
        "default.debug=true"   // Allow uncategorized qDebug
    );
    qDebug() << "Debug mode enabled";

    // List ALL available Qt resources
    qDebug() << "All Qt Resources:";
    QDirIterator it(":", QDirIterator::Subdirectories);
    while (it.hasNext()) {
      qDebug() << "Resource found:" << it.next();
    }

    // Check specific paths
    qDebug() << "Checking specific paths:";
    qDebug() << ":/pieces exists:" << QDir(":/pieces").exists();
    qDebug() << ":/pieces entries:" << QDir(":/pieces").entryList();
    qDebug() << ":/assets/pieces exists:" << QDir(":/assets/pieces").exists();
    qDebug() << ":/assets/pieces entries:"
             << QDir(":/assets/pieces").entryList();

    // Check if qrc was compiled
    qDebug() << "Build info:";
    qDebug() << "Working directory:" << QDir::currentPath();
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