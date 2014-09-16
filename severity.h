#ifndef SEVERITY_H
#define SEVERITY_H

#include "enum_to_string.h"
#include <QTextStream>
#include <QString>

enum class Severity { DEBUG, INFO, WARNING, ERROR, NONE, UNDEFINED };

inline std::ostream& operator<<(std::ostream& out, Severity sev) {
    return out << EnumToString<Severity>::toString(sev).toStdString();
}

inline QTextStream& operator<<(QTextStream& out, Severity sev) {
    return out << EnumToString<Severity>::toString(sev);
}

inline std::istream& operator>>(std::istream& in, Severity& sev) {
    std::string value;
    in >> value;
    sev = EnumToString<Severity>::fromString(QString::fromStdString(value));
    return in;
}

#endif // SEVERITY_H
