#ifndef GUIWRITER_H
#define GUIWRITER_H

#include <QWidget>
#include <QString>

#include "logwriter.h"

class GUIWriter : public LogWriter {
 public:
  explicit GUIWriter(Severity severity, QWidget* parent = 0);
  virtual ~GUIWriter();

  virtual void writeMessage(const Severity severity, const QString& message ) throw();

 private:
  QWidget*  parent_;

  GUIWriter();
  GUIWriter(const GUIWriter&);
  void operator=(const GUIWriter&);
};

#endif // GUIWRITER_H
