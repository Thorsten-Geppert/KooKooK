#pragma once

#include "lib/ServerConfigurationType.h"
#include "../lib/LogLibrary.h"
#include <QPointer>

class Configuration {

	public:
		enum class ErrorEnumeration:int {
			NONE = 0,
			ERROR = 1
		};

		Configuration();

		ErrorEnumeration load(QString configurationFilename = "");

		void setServer(const ServerConfigurationType &server);
		ServerConfigurationType getServer() const;

		bool log(
			const QString &message,
			const bool error = false,
			const qint64 pid = 0
		);
	
	private:
		ServerConfigurationType server;
		QPointer<LogLibrary> logLibrary;

};

