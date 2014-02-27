#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <sstream>
#include <QFile>
#include <QTextStream>

#include "logwriter.h"
#include "severity.h"

class QString;
class QFile;
class QStringStream;

class FileWriter : public LogWriter {
 public:

  enum class FileMode { BACKUP, OVERWRITE, APPEND };

  FileWriter(const Severity severity, const QString& file_name, const FileMode file_mode = FileMode::APPEND);
  virtual ~FileWriter();

  virtual void writeMessage(const Severity severity, const QString& message ) throw();

 private:
  QFile        log_file_;
  QTextStream  log_stream_;

  FileWriter();
  FileWriter(const FileWriter&);
  void operator=(const FileWriter&);
};

#endif // FILEWRITER_H
