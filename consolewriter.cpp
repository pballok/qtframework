#include <QDateTime>

#include <iostream>
#include <iomanip>

#include "consolewriter.h"
#include "severity.h"

using namespace std;

void ConsoleWriter::writeMessage(const Severity severity, const QString& message) throw() {
  QString timestamp = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");

  cerr << timestamp.toStdString() << " " << enumToString(severity) << " " << message.toStdString() << endl;
}
