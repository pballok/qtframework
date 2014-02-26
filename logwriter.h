#ifndef LOGWRITER_H
#define LOGWRITER_H

#include <QString>

#include "severity.h"

class LogWriter {
 public:
  explicit LogWriter(Severity severity) : min_severity_(severity) {}
  virtual ~LogWriter() {}

  Severity min_severity() const {
    return min_severity_;
  }

  void set_min_severity(const Severity severity) {
    min_severity_ = severity;
  }

  virtual void writeMessage(const Severity severity, const QString& message) = 0;

 protected:
  Severity  min_severity_;

 private:
  LogWriter();
  LogWriter(const LogWriter&);
  void operator=(const LogWriter&);
};

#endif
