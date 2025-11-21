# Collect all source files
set(CHESS_SOURCES
    # Core
    core/Color.cpp
    core/PieceType.cpp
    core/Position.cpp
    core/Logging.cpp
    
    # Bitboards
    bitboards/AttackTables.cpp
    bitboards/BitBoard.cpp
    bitboards/Manager.cpp
    bitboards/RayGenerator.cpp
    bitboards/SlidingAttacks.cpp
    
    # Game
    game/Board.cpp
    game/CastlingRights.cpp
    game/GameState.cpp
    game/MoveContext.cpp
    game/Move.cpp
    game/MoveGenerator.cpp
    game/MoveValidator.cpp
    
    # Pieces
    pieces/Bishop.cpp
    pieces/King.cpp
    pieces/Knight.cpp
    pieces/Pawn.cpp
    pieces/Piece.cpp
    pieces/PieceFactory.cpp
    pieces/Queen.cpp
    pieces/Rook.cpp
    
    # UI Widgets
    ui/widgets/SquareWidget.cpp
    ui/widgets/BoardWidget.cpp
    ui/widgets/StatusBarWidget.cpp
    ui/widgets/GameControlsWidget.cpp
    ui/widgets/MoveHistoryWidget.cpp
    ui/widgets/PromotionDialog.cpp
    
    # UI Windows
    ui/windows/GameWindow.cpp
    ui/windows/MainMenuWindow.cpp
    
    # UI Controllers
    ui/controllers/ChessGameController.cpp
    
    main.cpp
)

# Add resources
qt_add_resources(CHESS_RESOURCES
    ${CMAKE_SOURCE_DIR}/resources.qrc
)

# Create executable
add_executable(Chess ${CHESS_SOURCES} ${CHESS_RESOURCES})

# Include directories
target_include_directories(Chess PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link Qt libraries
target_link_libraries(Chess PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Svg
)