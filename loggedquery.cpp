#include <QSqlError>

#include <tracer.h>
#include <logger.h>

#include "loggedquery.h"

LoggedQuery::LoggedQuery(const QString& query, QSqlDatabase db) : QSqlQuery(query, db) {
    if(query != "") logQuery();
}

bool LoggedQuery::exec(const QString& query) {
  QSqlQuery::exec(query);
  logQuery();
  return isActive();
}

bool LoggedQuery::exec() {
  QSqlQuery::exec();
  logQuery();
  return isActive();
}

void LoggedQuery::logQuery() const {
  Tracer tracer("LoggedQuery::logQuery", lastQuery());

  if (isActive()) {
    if (isSelect()) {
      tracer << "Returned rows: " << size();
    } else {
      tracer << "Rows affected: " << numRowsAffected();
    }
  } else {
    Logger::instance() << Severity::ERROR << "MySQL returned with error: \""
                       << lastError().text() << "\"";
  }
}
