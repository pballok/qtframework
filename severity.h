#ifndef SEVERITY_H
#define SEVERITY_H

#include <string>
#include <iostream>
#include <QTextStream>

enum class Severity { NONE, ERROR, WARNING, INFO, DEBUG };

std::string& severityToString(Severity s);
std::ostream& operator<<(std::ostream& os, const Severity& s);
QTextStream& operator<<(QTextStream& os, const Severity& s);

#endif // SEVERITY_H
