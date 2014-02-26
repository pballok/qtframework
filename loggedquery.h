#ifndef LOGGEDQUERY_H
#define LOGGEDQUERY_H

#include <QSqlQuery>

class QString;
class QSqlResult;
class QSqlDatabase;

class LoggedQuery : public QSqlQuery {
 public:
  LoggedQuery(const QString& query = QString(), QSqlDatabase db = QSqlDatabase());
  virtual ~LoggedQuery() {}

  bool exec(const QString& query);
  bool exec();

 protected:
  void logQuery() const;

 private:
  LoggedQuery(const LoggedQuery&);
  void operator=(const LoggedQuery&);
};

#endif
