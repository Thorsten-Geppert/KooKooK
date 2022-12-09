#include "Configuration.h"
#include <QSettings>
#include <QStringList>
#include <QStringList>
#include <QSslConfiguration>
#include "Defaults.h"
#include "lib/PostgreSQLDatabaseConfigurationType.h"
#include "lib/MySQLDatabaseConfigurationType.h"
#include "lib/SQLiteDatabaseConfigurationType.h"
#include "../lib/SystemLogLibrary.h"
#include "../lib/ConsoleLogLibrary.h"
#include "../lib/TextLogLibrary.h"

Configuration::Configuration() {
}

Configuration::~Configuration() {
	if(database)
		delete database;
}

Configuration::ErrorEnumeration Configuration::load(QString configurationFilename) {
	if(configurationFilename.isEmpty())
		configurationFilename = Defaults::CONFIGURATION_FILENAME;

	QSettings settings(configurationFilename, QSettings::IniFormat);
	if(settings.status() == QSettings::NoError) {
		// Logging
		QString logLibraryType(settings.value("Log/Library", Defaults::LOG_LIBRARY).toString().toLower());
		if(!Defaults::LOG_LIBRARIES.contains(logLibraryType, Qt::CaseInsensitive))
			logLibraryType = Defaults::LOG_LIBRARY;

		if(logLibraryType == "text") {
			logLibrary = new TextLogLibrary(
				settings.value("Log/Filename").toString(),
				settings.value("Log/Fallback").toBool()
			);
		} else if(logLibraryType == "console") {
			logLibrary = new ConsoleLogLibrary;
		} else {
			logLibrary = new SystemLogLibrary;
		}

		// Server
		server.setHostname(settings.value("Server/Hostname", Defaults::HOSTNAME).toString());
		server.setPort(settings.value("Server/Port", Defaults::PORT).toUInt());
		server.setWaitSecondsAfterThreadsShutdown(settings.value("Server/WaitSecondsAfterThreadShutdown", QVariant::fromValue(Defaults::WAIT_SECONDS_AFTER_THREAD_SHUTDOWN)).toUInt());
		server.setThreads(settings.value("Server/Threads", QVariant::fromValue(Defaults::THREADS)).toUInt());
		server.setThreadConnections(settings.value("Server/ThreadConnections", QVariant::fromValue(Defaults::THREAD_CONNECTIONS)).toUInt());

		/// SSL
		auto &ssl = server.getSsl();
		ssl.setServerCaFilename(settings.value("Server/SSLServerCaFilename", Defaults::SSL_SERVER_CA_FILENAME).toString());
		ssl.setClientCaFilename(settings.value("Server/SSLClientCaFilename", Defaults::SSL_CLIENT_CA_FILENAME).toString());
		ssl.setKeyFilename(settings.value("Server/SSLKeyFilename", Defaults::SSL_KEY_FILENAME).toString());
		ssl.setCertificateFilename(settings.value("Server/SSLCertificatFilename", Defaults::SSL_CERTIFICATE_FILENAME).toString());
		ssl.setVerify(settings.value("Server/SSLVerify", Defaults::SSL_VERIFY).toBool());
		if(!ssl.cache(logLibrary)) {
			logLibrary->log("Error initialize ssl (create cache)");
			return ErrorEnumeration::SSL_INITIALIZE;
		}

		bool loadedCertificate = false;
		QSslCertificate serverCaCertificate = SslConfigurationType::loadCertificate(ssl.getServerCaFilename(), &loadedCertificate);
		if(!loadedCertificate) {
			logLibrary->log(QString("Could not load server ca file %1").arg(ssl.getServerCaFilename()));
			return ErrorEnumeration::SSL_LOAD_SERVER_CA_FILE;
		}

		QSslCertificate clientCaCertificate = SslConfigurationType::loadCertificate(ssl.getClientCaFilename(), &loadedCertificate);
		if(!loadedCertificate) {
			logLibrary->log(QString("Could not load client ca file %1").arg(ssl.getClientCaFilename()));
			return ErrorEnumeration::SSL_LOAD_CLIENT_CA_FILE;
		}

		QSslConfiguration sslConfiguration = QSslConfiguration::defaultConfiguration();
		sslConfiguration.addCaCertificates(QList<QSslCertificate>() << serverCaCertificate << clientCaCertificate);
		QSslConfiguration::setDefaultConfiguration(sslConfiguration);

		// Database
		QString databaseType(settings.value("Database/Type", Defaults::DATABASE_TYPE).toString().toLower());
		if(!Defaults::DATABASE_TYPES.contains(databaseType, Qt::CaseInsensitive)) {
			logLibrary->log(QString("Database driver %1 not available. Please use one of these: %2").arg(databaseType).arg(Defaults::DATABASE_TYPES.join(", ")));
			return ErrorEnumeration::DATABASE_DRIVER_ERROR;
		}

		if(databaseType == "postgresql") {
			database = new PostgreSQLDatabaseConfigurationType(
				settings.value("Database/Hostname", "localhost").toString(),
				settings.value("Database/Database", "kookook").toString(),
				settings.value("Database/Username", "pgsql").toString(),
				settings.value("Database/Password", "").toString(),
				settings.value("Database/Port", "5432").toInt()
			);
		} else if(databaseType == "mysql") {
			database = new MySQLDatabaseConfigurationType(
				settings.value("Database/Hostname", "localhost").toString(),
				settings.value("Database/Database", "kookook").toString(),
				settings.value("Database/Username", "mysql").toString(),
				settings.value("Database/Password", "mysql").toString(),
				settings.value("Database/Port", "3306").toInt()
			);
		} else {
			database = new SQLiteDatabaseConfigurationType(
				settings.value("Database/Database", "/tmp/kookook.sqlite").toString()
			);
		}

		if(database) {
			sqlDatabase = database->create();
			if(!sqlDatabase.open())
				return ErrorEnumeration::DATABASE_NOT_OPEN;
		}

		return ErrorEnumeration::NONE;
	}

	return ErrorEnumeration::ERROR;
}

void Configuration::setServer(const ServerConfigurationType &server) {
	this->server = server;
}

ServerConfigurationType &Configuration::getServer() {
	return server;
}

bool Configuration::log(
	const QString &message,
	const bool error,
	const qint64 pid
) {
	if(logLibrary.isNull()) {
		SystemLogLibrary systemLogLibrary;
		systemLogLibrary.log("Log system not initialized, see next error", true);
		systemLogLibrary.log(message, error);

		return false;
	}

	return logLibrary->log(message, error, pid);
}

QSqlDatabase &Configuration::getSqlDatabase() {
	return sqlDatabase;
}

QString Configuration::ErrorEnumerationToString(const ErrorEnumeration errorEnumeration) {
	QString message("Unknown error");

	switch(errorEnumeration) {
		case ErrorEnumeration::NONE:                    message = "NONE"; break;
		case ErrorEnumeration::ERROR:                   message = "ERROR"; break;
		case ErrorEnumeration::DATABASE_DRIVER_ERROR:   message = "DATABASE_DRIVER_ERROR"; break;
		case ErrorEnumeration::DATABASE_NOT_OPEN:       message = "DATABASE_NOT_OPEN"; break;
		case ErrorEnumeration::SSL_INITIALIZE:          message = "SSL_INITIALIZE"; break;
		case ErrorEnumeration::SSL_LOAD_SERVER_CA_FILE: message = "SSL_LOAD_SERVER_CA_FILE"; break;
		case ErrorEnumeration::SSL_LOAD_CLIENT_CA_FILE: message = "SSL_LOAD_CLIENT_CA_FILE"; break;
	}

	return message;
}
