#ifndef CONSOLEWRITER_H
#define CONSOLEWRITER_H

#include <QString>

#include "logwriter.h"
#include "severity.h"

class ConsoleWriter : public LogWriter {
 public:
  explicit ConsoleWriter(const Severity severity) : LogWriter(severity) {}
  virtual ~ConsoleWriter() {}

  virtual void writeMessage(const Severity severity,const QString& message ) throw();

 private:
  ConsoleWriter();
  ConsoleWriter(const ConsoleWriter&);
  void operator=(const ConsoleWriter&);
};

#endif
