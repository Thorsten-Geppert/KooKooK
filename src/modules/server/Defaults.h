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
		static const unsigned int THREADS;
		static const unsigned int THREAD_CONNECTIONS;
		static const QString SSL_SERVER_CA_FILENAME;
		static const QString SSL_CLIENT_CA_FILENAME;
		static const QString SSL_KEY_FILENAME;
		static const QString SSL_CERTIFICATE_FILENAME;
		static const bool SSL_VERIFY;

};

const QString Defaults::CONFIGURATION_FILENAME                   = "test";
const QString Defaults::HOSTNAME                                 = "localhost";
const quint16 Defaults::PORT                                     = 12345;
const QStringList Defaults::LOG_LIBRARIES                        = QStringList() << "System" << "Console" << "Text";
const QString Defaults::LOG_LIBRARY                              = LOG_LIBRARIES[0];
const unsigned long Defaults::WAIT_SECONDS_AFTER_THREAD_SHUTDOWN = 5;
const QString Defaults::DATABASE_TYPE                            = "SQLite";
const QStringList Defaults::DATABASE_TYPES                       = QStringList() << "SQLite" << "PostgreSQL" << "MySQL";
const unsigned int Defaults::THREADS                             = 10;
const unsigned int Defaults::THREAD_CONNECTIONS                  = 20;
const QString Defaults::SSL_SERVER_CA_FILENAME                   = "ServerCa.pem";
const QString Defaults::SSL_CLIENT_CA_FILENAME                   = "ClientCa.pem";
const QString Defaults::SSL_KEY_FILENAME                         = "ServerKey.key";
const QString Defaults::SSL_CERTIFICATE_FILENAME                 = "ServerCertificate.pem";
const bool Defaults::SSL_VERIFY                                  = true;
