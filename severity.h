#ifndef SEVERITY_H
#define SEVERITY_H

enum class Severity { DEBUG, INFO, WARNING, ERROR, NONE };

template <typename OS>
inline OS& operator<<(OS& os, const Severity& s) {
  switch(s) {
    case Severity::DEBUG:   return os << "DEB";
    case Severity::INFO:    return os << "INF";
    case Severity::WARNING: return os << "WAR";
    case Severity::ERROR:   return os << "ERR";
    case Severity::NONE:    return os << "NON";
    default:                return os << "INVALID SEVERITY";
  }
}

#endif // SEVERITY_H
