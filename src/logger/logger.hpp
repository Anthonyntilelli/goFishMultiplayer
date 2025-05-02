#ifndef LOGGER_H
#define LOGGER_H

#include <ctime>
#include <fstream>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <string>

/// @brief Logs actions for the server to a file.
/// This is a singleton class.
/// THis class does not manage the size of the file. It expect as log rotate
/// service to be used.
class Logger {
private:
  std::ofstream file{};
  std::mutex mtx{};
  const std::string filePath{};

  /// @brief Opens a file for the logs.
  /// @throw a "runtime_error" if the file cannot be opened.
  /// @param logFilePath path to log file.
  explicit Logger(const std::string &logFilePath);
  ~Logger();
  /// @brief Reopens the log file.
  /// @return returns false if could not re-open file.
  bool reopenLogFile();

public:
  /// @brief Gets the logger instance.
  /// @param logFilePath path to the log file to use, leave blank if instance
  /// already initalized.
  /// @return return the logger class.
  /// @throw "runtime_error" if LogFilePath is invalid
  static Logger &getInstance(const std::string &logFilePath = "");

  /// @brief logs message to the file, with a time stamp.
  /// @param message Message to be log to the file.
  void log(const std::string &message);

  /// @brief Gets the log file path.
  /// @return returns filePath.
  const std::string getLogPath() const;

  Logger() = delete;
  Logger(const Logger &cpy) = delete;
  Logger &operator=(const Logger &cpy) = delete;
  Logger(Logger &org) = delete;
  Logger &operator=(Logger &&org) = delete;
};
#endif