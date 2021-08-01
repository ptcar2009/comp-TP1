#include "logs.h"

#include <iostream>

void logger::Logger::SetLogLevel(logger::LogLevel verbosity) {
    this->verbosity = verbosity;
};
logger::LogLevel logger::Logger::GetLogLevel() { return verbosity; }

logger::Logger::Logger(std::ostream& _out) : out(_out) {
    if (getenv("VERBOSITY") != NULL)
	verbosity = LogLevel(atoi(getenv("VERBOSITY")));
}
logger::Logger::Logger(logger::LogLevel _verbosity, std::ostream& _out)
    : verbosity(_verbosity), out(_out) {}
