#include <QFile>
#include <QDir>
#include <QString>
#include <QTextStream>
#include <QStringList>
#include <QSqlDatabase>

#include <logmessage.h>
#include <filewriter.h>
#include <loggedquery.h>

#include "testpreferences.h"
#include "frameworktest.h"

using namespace std;

void FrameworkTest::fileLogger() {
    QString file_name_1 = "writertest_1.log";
    QFile log_file_1(file_name_1);
    QVERIFY(log_file_1.open(QIODevice::Truncate | QIODevice::WriteOnly
                            | QIODevice::Text));
    QTextStream out(&log_file_1);
    out << "Old Text 01" << "\n";
    out << "Old Text 02" << "\n";
    log_file_1.close();

    QString file_name_2 = "writertest_2.log";
    QFile::remove(file_name_2);
    QVERIFY(log_file_1.copy(file_name_2));
    QFile log_file_2(file_name_2);

    QString file_name_3 = "writertest_3.log";
    QFile log_file_3(file_name_3);

    FileWriter file_writer_1(Severity::INFO, file_name_1, FileWriter::FileMode::APPEND);
    Logger::instance().registerWriter(&file_writer_1);

    FileWriter file_writer_2(Severity::ERROR, file_name_2, FileWriter::FileMode::BACKUP);
    Logger::instance().registerWriter(&file_writer_2);

    FileWriter file_writer_3(Severity::DEBUG, file_name_3, FileWriter::FileMode::OVERWRITE);
    Logger::instance().registerWriter(&file_writer_3);

    QDir current_dir = QDir::current();
    QStringList backups =
            current_dir.entryList(QStringList(QString("%1-*").arg(file_name_2)),
                                  QDir::Files, QDir::Time | QDir::Reversed);
    QString file_name_4 = backups.first();
    QFile log_file_4(file_name_4);

    LOG(INFO) << "Message 01" << LOG_EOM;
    LOG(DEBUG) << "Message 02" << LOG_EOM;
    LOG(ERROR) << "Message 03" << LOG_EOM;

    QVERIFY(log_file_1.exists());
    QVERIFY(log_file_1.open(QIODevice::ReadOnly | QIODevice::Text));

    QVERIFY(log_file_2.exists());
    QVERIFY(log_file_2.open(QIODevice::ReadOnly | QIODevice::Text));

    QVERIFY(log_file_3.exists());
    QVERIFY(log_file_3.open(QIODevice::ReadOnly | QIODevice::Text));

    QVERIFY(log_file_4.exists());
    QVERIFY(log_file_4.open(QIODevice::ReadOnly | QIODevice::Text));

    QString contents_1 = log_file_1.readAll();
    QVERIFY(!contents_1.isEmpty());
    QVERIFY(contents_1.contains("Old Text 01"));
    QVERIFY(contents_1.contains("Old Text 02"));
    QVERIFY(contents_1.contains("INF Message 01"));
    QVERIFY(!contents_1.contains("DEB Message 02"));
    QVERIFY(contents_1.contains("ERR Message 03"));

    QString contents_2 = log_file_2.readAll();
    QVERIFY(!contents_2.isEmpty());
    QVERIFY(!contents_2.contains("Old Text 01"));
    QVERIFY(!contents_2.contains("Old Text 02"));
    QVERIFY(!contents_2.contains("INF Message 01"));
    QVERIFY(!contents_2.contains("DEB Message 02"));
    QVERIFY(contents_2.contains("ERR Message 03"));

    QString contents_3 = log_file_3.readAll();
    QVERIFY(!contents_3.isEmpty());
    QVERIFY(!contents_3.contains("Old Text 01"));
    QVERIFY(!contents_3.contains("Old Text 02"));
    QVERIFY(contents_3.contains("INF Message 01"));
    QVERIFY(contents_3.contains("DEB Message 02"));
    QVERIFY(contents_3.contains("ERR Message 03"));

    QString contents_4 = log_file_4.readAll();
    QVERIFY(!contents_4.isEmpty());
    QVERIFY(contents_4.contains("Old Text 01"));
    QVERIFY(contents_4.contains("Old Text 02"));
    QVERIFY(!contents_4.contains("INF Message 01"));
    QVERIFY(!contents_4.contains("DEB Message 02"));
    QVERIFY(!contents_4.contains("ERR Message 03"));

    Logger::destroy();
}

void FrameworkTest::preferences() {
    TestPreferences preferences("test", "1.0");

    QCOMPARE(preferences.app_name(), QString("test"));
    QCOMPARE(preferences.iniFileName(), QString("test.ini"));
    QCOMPARE(preferences.version(), QString("1.0"));

    QString ini_file_name = preferences.iniFileName();
    QFile::remove(ini_file_name);

    QFile settings_file(ini_file_name);

    preferences.set_value(5);
    preferences.save();
    QVERIFY(settings_file.exists());
    QVERIFY(settings_file.open(QIODevice::ReadOnly | QIODevice::Text));

    QString contents=settings_file.readAll();
    QVERIFY(contents.contains("Value=5"));

    settings_file.close();

    preferences.set_value(6);
    preferences.save();
    QVERIFY(settings_file.open(QIODevice::ReadOnly | QIODevice::Text));

    contents=settings_file.readAll();
    QVERIFY(contents.contains("Value=6"));
}

void FrameworkTest::loggedquery() {
    QString file_name = "test.log";
    QFile log_file(file_name);
    FileWriter log_writer(Severity::DEBUG, file_name, FileWriter::FileMode::OVERWRITE);
    Logger::instance().registerWriter(&log_writer);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("framework_test");
    db.setUserName("framework_test");
    db.setPassword("framework_test");
    QVERIFY(db.open());

    QString query_string_1 = "SELECT * FROM test";
    LoggedQuery query_1;
    QVERIFY(query_1.exec(query_string_1));
    QCOMPARE(query_1.size(),3);

    QString query_string_2 = "SELECT * FROM test WHERE column_3=\"Message_2\"";
    LoggedQuery query_2(query_string_2);
    QCOMPARE(query_2.size(),1);

    QString query_string_3 = "SELECT * FROM test2";
    LoggedQuery query_3;
    QVERIFY(!query_3.exec(query_string_3));
    QCOMPARE(query_3.size(),-1);

    QVERIFY(log_file.exists());
    QVERIFY(log_file.open(QIODevice::ReadOnly | QIODevice::Text));
    QString contents = log_file.readAll();
    QVERIFY(!contents.isEmpty());
    QVERIFY(contents.contains(query_string_1));
    QVERIFY(contents.contains("Returned rows: 3"));
    QVERIFY(contents.contains(query_string_2));
    QVERIFY(contents.contains("Returned rows: 1"));
    QVERIFY(contents.contains(query_string_3));
    QVERIFY(contents.contains("MySQL returned with error"));

    Logger::destroy();
}

void FrameworkTest::enumToString() {
    QCOMPARE(QString("DEB"), EnumToString<Severity>::toString(Severity::DEBUG));
    QCOMPARE(QString("WAR"), EnumToString<Severity>::toString(Severity::WARNING));
    QCOMPARE(QString("UNKNOWN ENUM VALUE"), EnumToString<Severity>::toString(Severity::UNDEFINED));

    QVERIFY(Severity::DEBUG == EnumToString<Severity>::fromString("DEB"));
    QVERIFY(Severity::WARNING == EnumToString<Severity>::fromString("WAR"));
    QVERIFY(Severity::UNDEFINED == EnumToString<Severity>::fromString("RANDOM_STRING"));
}
