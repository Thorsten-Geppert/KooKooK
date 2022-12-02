#pragma once

#include <QString>
#include <QStringList>

class Defaults {

	public:
		static const QString CONFIGURATION_FILENAME;
		static const QString HOSTNAME;
		static const quint16 PORT;
		static const QString LOG_LIBRARY;
		static const QStringList LOG_LIBRARIES;
		static const unsigned long WAIT_SECONDS_AFTER_THREAD_SHUTDOWN;
		static const QString DATABASE_TYPE;
		static const QStringList DATABASE_TYPES;

};

const QString Defaults::CONFIGURATION_FILENAME                   = "test";
const QString Defaults::HOSTNAME                                 = "localhost";
const quint16 Defaults::PORT                                     = 12345;
const QStringList Defaults::LOG_LIBRARIES                        = QStringList() << "System" << "Console" << "Text";
const QString Defaults::LOG_LIBRARY                              = LOG_LIBRARIES[0];
const unsigned long Defaults::WAIT_SECONDS_AFTER_THREAD_SHUTDOWN = 5;
const QString Defaults::DATABASE_TYPE                            = "SQLite";
const QStringList Defaults::DATABASE_TYPES                       = QStringList() << "SQLite" << "PostgreSQL" << "MySQL";
