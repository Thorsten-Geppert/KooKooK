#pragma once

#include "lib/ServerConfigurationType.h"
#include "../lib/LogLibrary.h"
#include <QPointer>

class Configuration {

	public:
		Configuration();

		bool load(QString configurationFilename = "");

		void setServer(const ServerConfigurationType &server);
		ServerConfigurationType getServer() const;

		bool log(
			const QString &message,
			const bool error = false
		);
	
	private:
		ServerConfigurationType server;
		QPointer<LogLibrary> logLibrary;

};

