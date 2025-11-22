#include "Logging.h"
#include <QDateTime>

// Define Qt logging categories with default severity levels
Q_LOGGING_CATEGORY(uiDebug, "ui", QtWarningMsg)
Q_LOGGING_CATEGORY(gameDebug, "game", QtWarningMsg)
Q_LOGGING_CATEGORY(resourceDebug, "resources", QtDebugMsg)
Q_LOGGING_CATEGORY(moveDebug, "move", QtDebugMsg)
Q_LOGGING_CATEGORY(boardDebug, "board", QtDebugMsg)

// Initialize static members
std::atomic<int> Logger::s_callCounter{0};
thread_local int Logger::t_currentCallId = -1;

/**
 * @brief Generate next unique call ID
 *
 * Thread-safe atomic increment of global counter
 *
 * @return int Next unique call ID
 */
int Logger::nextId() { return s_callCounter.fetch_add(1); }

/**
 * @brief Get current thread's call ID
 *
 * Returns -1 if no FunctionScope is active
 *
 * @return int Current call ID for this thread
 */
int Logger::getCurrentId() { return t_currentCallId; }

/**
 * @brief Construct FunctionScope and create new call context
 *
 */
Logger::FunctionScope::FunctionScope() : m_previousId(t_currentCallId) {
  m_id = nextId();
  t_currentCallId = m_id;
}

/**
 * @brief Destroy FunctionScope and restore previous call context
 */
Logger::FunctionScope::~FunctionScope() { t_currentCallId = m_previousId; }

/**
 * @brief Core logging implementation
 *
 * Format: HH:mm:ss.zzz | category | callId | message
 *
 * @param level Log severity level
 * @param category Qt logging category
 * @param message Log message content
 */
void Logger::log(Level level, const QLoggingCategory &category,
                 const std::string &message) {
  int callId = getCurrentId();

  QString timestamp = QDateTime::currentDateTime().toString("HH:mm:ss.zzz");
  QString formatted = QString("%1 | %2 | %3 | %4")
                          .arg(timestamp)
                          .arg(category.categoryName(), -8)
                          .arg(callId, 4)
                          .arg(QString::fromStdString(message));

  switch (level) {
  case Level::Debug:
    qCDebug(category).noquote() << formatted;
    break;
  case Level::Info:
    qCInfo(category).noquote() << formatted;
    break;
  case Level::Warning:
    qCWarning(category).noquote() << formatted;
    break;
  case Level::Critical:
    qCCritical(category).noquote() << formatted;
    break;
  }
}

/**
 * @brief Log message at debug level
 *
 * @param category Qt logging category
 * @param message Log message content
 */
void Logger::debug(const QLoggingCategory &category,
                   const std::string &message) {
  log(Level::Debug, category, message);
}

/**
 * @brief Log message at info level
 *
 * @param category Qt logging category
 * @param message Log message content
 */
void Logger::info(const QLoggingCategory &category,
                  const std::string &message) {
  log(Level::Info, category, message);
}

/**
 * @brief Log message at warning level
 *
 * @param category Qt logging category
 * @param message Log message content
 */
void Logger::warning(const QLoggingCategory &category,
                     const std::string &message) {
  log(Level::Warning, category, message);
}

/**
 * @brief Log message at critical level
 *
 * @param category Qt logging category
 * @param message Log message content
 */
void Logger::critical(const QLoggingCategory &category,
                      const std::string &message) {
  log(Level::Critical, category, message);
}