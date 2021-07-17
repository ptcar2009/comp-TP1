#ifndef LOGS_HPP
#define LOGS_HPP

#include <iostream>

namespace logger {
class Logger {
  public:
   template <typename T>
   void ERROR(T t) {
      printv("\e[31mERROR\e[0m\t- ", t);
      std::cerr << std::endl;
      exit(1);
   }
   template <typename T, typename... Args>
   void ERROR(const T t, Args... args) {
      printv("\e[31mERROR\e[0m\t- ", *t, args...);
      std::cerr << std::endl;
      exit(1);
   }
   template <typename T>
   void INFO(T t) {
      if (!verbosity) return;
      printv("\e[33mINFO\e[0m\t- ", t);
      std::cerr << std::endl;
   }
   template <typename T, typename... Args>
   void INFO(T t, Args... args) {
      if (!verbosity) return;
      printv("\e[33mINFO\e[0m\t- ", t, args...);
      std::cerr << std::endl;
   }

   template <typename T>
   void DEBUG(T t) {
      if (verbosity < 2) return;
      printv("\e[34mDEBUG\e[0m\t- ", t);
      std::cerr << std::endl;
   }

   template <typename T, typename... Args>
   void DEBUG(T t, Args... args) {
      if (verbosity < 2) return;
      printv("\e[34mDEBUG\e[0m\t- ", t, args...);
      std::cerr << std::endl;
   }
   Logger();

  private:
   int verbosity;
   template <typename T>
   void printv(T t) {
      std::cerr << t << " ";
   }

   template <typename T, typename... Args>
   void printv(T t, Args... args)  // recursive variadic function
   {
      std::cerr << t << " ";

      printv(args...);
   }
};

};  // namespace logger

#endif  // LOGS_HPP
