#include "severity.h"

template<>
EnumToString<Severity>::MapType EnumToString<Severity>::initEnumStrings() {
    EnumToString<Severity>::MapType map;
    map.insert(Severity::DEBUG, "DEB");
    map.insert(Severity::INFO, "INF");
    map.insert(Severity::WARNING, "WAR");
    map.insert(Severity::ERROR, "ERR");
    map.insert(Severity::NONE, "NON");

    return map;
}

template<>
const EnumToString<Severity>::MapType EnumToString<Severity>::map_ = EnumToString<Severity>::initEnumStrings();

