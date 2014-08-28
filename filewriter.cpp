#include <QDateTime>

#include "filewriter.h"

FileWriter::FileWriter(const Severity severity, const QString& file_name, const FileMode file_mode) : LogWriter(severity)
{
  log_file_.setFileName(file_name);
  switch (file_mode) {
    case FileMode::BACKUP: {
      if (log_file_.exists()) {
        QString timestamp =
            QDateTime::currentDateTime().toString("ddMMyyyy_hhmmss");
        QString backup_file_name = file_name;
        backup_file_name.append("-").append(timestamp);
        log_file_.copy(backup_file_name);
      }
      /* No break here because BACKUP continues with same functionality as
       * OVERWRITE */
    }
    case FileMode::OVERWRITE: {
      log_file_.open(QIODevice::Truncate | QIODevice::WriteOnly |
                     QIODevice::Text);
      break;
    }
    default: {   /* FileMode::APPEND mode is the default */
      log_file_.open(QIODevice::Append | QIODevice::WriteOnly |
                     QIODevice::Text);
      break;
    }
  }
  log_stream_.setDevice(&log_file_);
}

FileWriter::~FileWriter() {
  log_file_.close();
}

void FileWriter::writeMessage(const Severity severity, const QString& message) throw() {
  QString timestamp = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");

  log_stream_ << timestamp << " " << enumToQString(severity) << " " << message << endl;
}
