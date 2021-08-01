#ifndef LOGS_HPP
#define LOGS_HPP

#include <iostream>

namespace logger {
enum LogLevel { ERROR, INFO, DEBUG };
/**
 * @brief Customizeable logger with templated prints.
 */
class Logger {
 public:
  /**
   * @brief Prints an object with the log level ERROR and then exits with an error.
   *
   * @tparam T Type of the object that will be printed.
   * @param t Object that will be printed.
   */
  template <typename T>
  void ERROR(T t) {
    printv("\e[31mERROR\e[0m\t- ", t);
    out << std::endl;
    exit(1);
  }
  /**
   * @brief Prints objects, separated by spaces, at the log level ERROR and then exits with an error.
   *
   * @tparam T Type of the first object to be printed.
   * @tparam Args Type of the other objecs.
   * @param t First object to be printed.
   * @param args Other objects to be printed.
   */
  template <typename T, typename... Args>
  void ERROR(const T t, Args... args) {
    printv("\e[31mERROR\e[0m\t- ", *t, args...);
    out << std::endl;
    exit(1);
  }

  /**
   * @brief Prints an object with the log level INFO.
   *
   * @tparam T Type of the object that will be printed.
   * @param t Object that will be printed.
   */
  template <typename T>
  void INFO(T t) {
    if (verbosity < LogLevel::INFO) return;
    printv("\e[33mINFO\e[0m\t- ", t);
    out << std::endl;
  }

  /**
   * @brief Prints objects, separated by spaces, at the log level INFO.
   *
   * @tparam T Type of the first object to be printed.
   * @tparam Args Type of the other objecs.
   * @param t First object to be printed.
   * @param args Other objects to be printed.
   */
  template <typename T, typename... Args>
  void INFO(T t, Args... args) {
    if (verbosity < LogLevel::INFO) return;
    printv("\e[33mINFO\e[0m\t- ", t, args...);
    out << std::endl;
  }

  /**
   * @brief Prints an object with the log level INFO.
   *
   * @tparam T Type of the object that will be printed.
   * @param t Object that will be printed.
   */
  template <typename T>
  void DEBUG(T t) {
    if (verbosity < LogLevel::DEBUG) return;
    printv("\e[34mDEBUG\e[0m\t- ", t);
    out << std::endl;
  }

  /**
   * @brief Prints objects, separated by spaces, at the log level DEBUG.
   *
   * @tparam T Type of the first object to be printed.
   * @tparam Args Type of the other objecs.
   * @param t First object to be printed.
   * @param args Other objects to be printed.
   */
  template <typename T, typename... Args>
  void DEBUG(T t, Args... args) {
    if (verbosity < LogLevel::DEBUG) return;
    printv("\e[34mDEBUG\e[0m\t- ", t, args...);
    out << std::endl;
  }

  /**
   * @brief Sets the log level of the logger.
   *
   * @param verbosity Log level that will be set.
   */
  void SetLogLevel(LogLevel verbosity);

  /**
   * @brief Returns the current log level of the logger.
   *
   * @return Log level of the logger.
   */
  LogLevel GetLogLevel();

  /**
   * @brief Instantiates a logger based on the environment variable "VERBOSITY". The variable should be a number between 0 and 2 both inclusive,
   * representing ERROR, INFO and DEBUG, respectively.
   *
   */
  Logger(std::ostream& out = std::cerr);


  /**
   * @brief Instantiates a logger with the given log level that writes on `out`.
   *
   * @param verbosity Log level of the logger.
   * @param out Output stream on which the logger will write to.
   */
  Logger(LogLevel verbosity, std::ostream& out = std::cerr);


 private:
  LogLevel verbosity;
  template <typename T>
  void printv(T t) {
    out << t << " ";
  }

  template <typename T, typename... Args>
  void printv(T t, Args... args)  // recursive variadic function
  {
    out << t << " ";

    printv(args...);
  }

  std::ostream& out;
};

};  // namespace logger

#endif  // LOGS_HPP
