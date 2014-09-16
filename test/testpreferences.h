#ifndef TESTPREFERENCES_H
#define TESTPREFERENCES_H

#include <QString>

#include <preferences.h>

class TestPreferences : public Preferences {
public:

    TestPreferences() : Preferences(), value_(0) {
    }

    TestPreferences(const QString& app_name, const QString& version)
        : Preferences(app_name, version),
          value_(0) {
    }

    ~TestPreferences() {
    }

    int value() const {
        return value_;
    }

    void set_value(int value) {
        value_ = value;
    }

protected:

  virtual void readSettings(const QSettings& settings_file);
  virtual void writeSettings(QSettings& settings_file) const;

  int    value_;
};

#endif // TESTPREFERENCES_H
