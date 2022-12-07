#pragma once

#include "lib/ServerConfigurationType.h"
#include "lib/DatabaseConfigurationType.h"
#include "../lib/LogLibrary.h"
#include <QPointer>
#include <QSqlDatabase>
#include <memory>

class Configuration {

	public:
		enum class ErrorEnumeration:int {
			NONE = 0,
			ERROR = 1,
			DATABASE_DRIVER_ERROR,
			DATABASE_NOT_OPEN,
			SSL_INITIALIZE,
			SSL_LOAD_SERVER_CA_FILE,
			SSL_LOAD_CLIENT_CA_FILE
		};

		Configuration();
		~Configuration();

		ErrorEnumeration load(QString configurationFilename = "");

		void setServer(const ServerConfigurationType &server);
		ServerConfigurationType &getServer();

		bool log(
			const QString &message,
			const bool error = false,
			const qint64 pid = 0
		);

		QSqlDatabase &getSqlDatabase();

		static QString ErrorEnumerationToString(const ErrorEnumeration errorEnumeration);
	
	private:
		ServerConfigurationType server;
		// TODO replace with smart pointer
		DatabaseConfigurationType *database = nullptr;
		QSqlDatabase sqlDatabase;
		QPointer<LogLibrary> logLibrary;

};

