#include "testpreferences.h"

void TestPreferences::readSettings(const QSettings &settings_file) {
  value_ = settings_file.value("Value", 0).toUInt();
}

void TestPreferences::writeSettings(QSettings &settings_file) const {
  settings_file.setValue("Value", value_);
}
