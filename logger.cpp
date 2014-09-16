#include "logger.h"
#include "logwriter.h"

Logger*  Logger::instance_ = nullptr;
Severity Logger::lowest_severity = Severity::NONE;

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
    instance_ = nullptr;
  }
}

void Logger::registerWriter(LogWriter* const writer) {
  writers_.append(writer);
  if (writer->min_severity() < Logger::lowest_severity)
    Logger::lowest_severity = writer->min_severity();
}

void Logger::writeMessage(const Severity severity, const QString& message) const {
  for(LogWriter* w : writers_) {
      if (severity >= w->min_severity())
        w->writeMessage(severity, message);
  }
}
