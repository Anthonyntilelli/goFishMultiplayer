#include "logger.hpp"

Logger::Logger(const std::string &logFilePath)
    : file{logFilePath, std::ios::app}, filePath{logFilePath} {
  if (!file.is_open())
    throw std::runtime_error("Cannot open the log file at: " + logFilePath +
                             ".");
}

Logger::~Logger() {
  if (file.is_open())
    file.close();
}

bool Logger::reopenLogFile() {
  if (!file.is_open()) {
    file.open(filePath, std::ios::app);

    if (!file.is_open()) {
      std::cerr << "ERROR: Unable to reopen log file!" << std::endl;
      return false;
    }
  }
  return true;
}

Logger &Logger::getInstance(const std::string &logFilePath) {
  static Logger instance(logFilePath);
  if (logFilePath != instance.getLogPath() && !logFilePath.empty()) {
    throw std::runtime_error(
        "Logger already initialized with different path: '" +
        instance.getLogPath() + "', attempted: '" + logFilePath + "'");
  }
  return instance;
}

void Logger::log(const std::string &message) {
  std::lock_guard<std::mutex> lck(mtx);
  const std::time_t now = std::time(nullptr);
  char buf[20];
  std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
  const std::string fullMessage = "[" + std::string{buf} + "] " + message;

  if (reopenLogFile()) {
    file << fullMessage << std::endl;
    file.flush();
  } else {
    std::cerr << "ERROR: Could not write log (" << fullMessage << ")"
              << std::endl;
  }
}

const std::string Logger::getLogPath() const { return filePath; }
