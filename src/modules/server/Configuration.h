#pragma once

#include "lib/ServerConfigurationType.h"
#include "lib/DatabaseConfigurationType.h"
#include "../lib/LogLibrary.h"
#include <QPointer>
#include <memory>

class Configuration {

	public:
		enum class ErrorEnumeration:int {
			NONE = 0,
			ERROR = 1,
			DATABASE_DRIVER_ERROR
		};

		Configuration();
		~Configuration();

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
		// TODO replace with smart pointer
		DatabaseConfigurationType *database = nullptr;
		QPointer<LogLibrary> logLibrary;

};

