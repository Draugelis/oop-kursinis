#pragma once

#include <QLoggingCategory>
#include <QString>
#include <atomic>
#include <string>

Q_DECLARE_LOGGING_CATEGORY(uiDebug)
Q_DECLARE_LOGGING_CATEGORY(gameDebug)
Q_DECLARE_LOGGING_CATEGORY(resourceDebug)
Q_DECLARE_LOGGING_CATEGORY(moveDebug)
Q_DECLARE_LOGGING_CATEGORY(boardDebug)

/**
 * @brief Logger class for providing convenient way to have clean logs
 *
 * Logger provides formatted logging with automatic call ID tracking.
 * Uses RAII FunctionScope to group logs from the same function call.
 */
class Logger {
private:
  // Global counter for generating unique call IDs
  static std::atomic<int> s_callCounter;
  // Current call ID within function scope
  static thread_local int t_currentCallId;
  // Generate next unique call ID
  static int nextId();
  // Get current call ID for this thread
  static int getCurrentId();

public:
  enum class Level { Debug, Info, Warning, Critical };

  /**
   * @brief RAII helper to manage function call context for logging
   *
   * @see
   * https://www.geeksforgeeks.org/cpp/resource-acquisition-is-initialization/
   *
   * Creates a new call ID when constructed and restores previous ID when
   * destroyed. All logs within the same scope share the same call ID.
   * Use at the start of functions to group related log entries.
   */
  class FunctionScope {
  private:
    // This scope's unique call ID
    int m_id;
    // Previous call ID to restore on destruction (for nested calls)
    int m_previousId;

  public:
    // Create new call context with unique ID
    FunctionScope();
    // Restore previous call context
    ~FunctionScope();
    // Get this scope's call ID
    int getId() const { return m_id; }
  };

  // Core logging method
  static void log(Level level, const QLoggingCategory &category,
                  const std::string &message);

  // log method wrappers with levels built-in
  static void debug(const QLoggingCategory &category,
                    const std::string &message);
  static void info(const QLoggingCategory &category,
                   const std::string &message);
  static void warning(const QLoggingCategory &category,
                      const std::string &message);
  static void critical(const QLoggingCategory &category,
                       const std::string &message);
};
