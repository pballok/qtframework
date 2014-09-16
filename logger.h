#ifndef LOGGER_H
#define LOGGER_H

#include <QList>

#include "severity.h"
#include "sevexception.h"

class LogWriter;
class QString;

class Logger {
 public:
  static Severity lowest_severity;

  static Logger& instance();
  static void destroy();
  
  void  registerWriter(LogWriter* const writer);

  void  writeMessage(const Severity severity, const QString& message ) const;

  inline Logger& operator<<(const SevException& exception) {
    writeMessage(exception.severity(), exception.what());
    return *this;
  }

 private:
  Logger() {}
  Logger(Logger const&);
  Logger& operator=(Logger const&);

  static Logger*     instance_;
  QList<LogWriter*>  writers_;
};

#endif
