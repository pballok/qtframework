#ifndef FRAMEWORKTEST_H
#define FRAMEWORKTEST_H

#include <QtTest>

class FrameworkTest : public QObject {

 Q_OBJECT

 private slots:
  void fileLogger();
  void preferences();
  void loggedquery();
  void enumToString();
};

#endif

