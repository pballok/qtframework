#include <QDateTime>

#include <iostream>
#include <iomanip>

#include "consolewriter.h"

using namespace std;

void ConsoleWriter::writeMessage(const Severity severity, const QString& message) throw() {
  if (severity <= min_severity_) {
    QString timestamp =
        QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");

    cerr << timestamp.toStdString() << " " << severity << " " << message.toStdString() << endl;
  }
}
