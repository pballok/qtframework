#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QString>
#include <QSettings>

#include <sevexception.h>

const unsigned int QTFRAMEWORK_VERSION_MAJOR = 1;
const unsigned int QTFRAMEWORK_VERSION_MINOR = 0;
const unsigned int QTFRAMEWORK_VERSION_PATCH = 0;

class Preferences {
public:
    Preferences()
        : app_name_(""),
          version_(""),
          file_name_("") {
    }

    Preferences(const QString& app_name, const QString& version) {
        set_app_name(app_name);
        set_version(version);
    }

    virtual ~Preferences() {}

    QString app_name() const {
        return app_name_;
    }

    void set_app_name(const QString& app_name) {
        app_name_ = app_name;
        file_name_ = app_name + ".ini";
    }

    QString version() const {
        return version_;
    }

    void set_version(const QString& version) {
        version_ = version;
    }

    QString iniFileName() const {
        return file_name_;
    }

    void load() throw(SevException);
    void save() const throw(SevException);

protected:

    virtual void readSettings(const QSettings& settings_file) = 0;
    virtual void writeSettings(QSettings& settings_file) const = 0;

private:
    QString app_name_;
    QString version_;
    QString file_name_;
};

#endif
