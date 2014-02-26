#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <QList>

#include "severity.h"
#include "sevexception.h"
#include "logmessage.h"

class LogWriter;

class Logger {
 public:
  static Logger& instance();
  static void destroy();
  
  void  registerWriter(LogWriter* const writer);

  void  writeMessage(const Severity severity, const QString& message ) const;

  inline LogMessage operator<<(const Severity severity) const {
    return LogMessage(severity);
  }

  inline Logger& operator<<(const SevException& exception) {
    writeMessage(exception.severity(), exception.what());
    return *this;
  }

 private:
  Logger();
  Logger(Logger const&);
  Logger& operator=(Logger const&);

  static Logger*     instance_;
  QList<LogWriter*>  writers_;
};

#endif
