#include "logger.h"
#include "logwriter.h"

Logger* Logger::instance_ = nullptr;

Logger& Logger::instance() {
  if (!instance_) {
    instance_ = new Logger();
    atexit(Logger::destroy);
  }

  return *instance_;
}

void Logger::destroy() {
  if (instance_) {
    delete instance_;
    instance_ = NULL;
  }
}

void Logger::registerWriter(LogWriter* const writer) {
  writers_.append(writer);
}

void Logger::writeMessage(const Severity severity, const QString& message) const {
  for(LogWriter* w : writers_) {
    w->writeMessage(severity, message);
  }
}
