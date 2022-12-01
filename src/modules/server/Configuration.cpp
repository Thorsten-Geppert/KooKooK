#include "Configuration.h"
#include <QSettings>
#include <QStringList>
#include "Defaults.h"
#include "../lib/SystemLogLibrary.h"
#include "../lib/ConsoleLogLibrary.h"
#include "../lib/TextLogLibrary.h"

Configuration::Configuration() {
}

bool Configuration::load(QString configurationFilename) {
	if(configurationFilename.isEmpty())
		configurationFilename = Defaults::CONFIGURATION_FILENAME;

	QSettings settings(configurationFilename, QSettings::IniFormat);
	if(settings.status() == QSettings::NoError) {
		// Server
		server.setHostname(settings.value("Server/Hostname", Defaults::HOSTNAME).toString());
		server.setPort(settings.value("Server/Port", Defaults::PORT).toUInt());

		// Logging
		qDebug() << "Logging";
		auto logLibraryType = settings.value("Log/Library", Defaults::LOG_LIBRARY).toString().toLower();
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

		return true;
	}

	return false;
}

void Configuration::setServer(const ServerConfigurationType &server) {
	this->server = server;
}

ServerConfigurationType Configuration::getServer() const {
	return server;
}

bool Configuration::log(
	const QString &message,
	const bool error
) {
	if(logLibrary.isNull()) {
		SystemLogLibrary systemLogLibrary;
		systemLogLibrary.log("Log system not initialized, see next error", true);
		systemLogLibrary.log(message, error);

		return false;
	}

	return logLibrary->log(message, error);
}
