#ifndef ENUM_TO_STRING_H
#define ENUM_TO_STRING_H

#include <QMap>
#include <QString>

template<typename T>
class EnumToString {
public:
    typedef QMap<T, QString> MapType;

    static MapType initEnumStrings();

    static QString toString(const T& enumVal) {
        return map_.value(enumVal, "UNKNOWN ENUM VALUE");
    }

    static T fromString(const QString& stringVal) {
        return map_.key(stringVal, T::UNDEFINED);
    }

private:
    static const MapType map_;
};

#endif
