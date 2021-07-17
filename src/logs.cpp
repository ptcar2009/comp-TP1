#include "logs.h"

#include <iostream>

namespace logger {
Logger::Logger() {
    if (getenv("VERBOSITY") != NULL) verbosity = atoi(getenv("VERBOSITY"));
}
}  // namespace logger

