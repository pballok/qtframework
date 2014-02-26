#ifndef LOGMESSAGE_H
#define LOGMESSAGE_H

#include <QString>
#include <QTextStream>

#include "severity.h"

class LogMessage {
 public:
  enum class LoggerManip { EOM, CLEAR };

  explicit LogMessage(const Severity severity);
  LogMessage(const LogMessage& that);
  ~LogMessage();

  template<typename T>
  LogMessage& operator<<(const T param) {
    message_stream_ << param;
    return *this;
  }

  LogMessage& operator<<(const LoggerManip manipulator);

 private:
  Severity      severity_;
  QString       message_;
  QTextStream   message_stream_;

  LogMessage();
  void operator=(const LogMessage&);
};

#endif // LOGMESSAGE_H
