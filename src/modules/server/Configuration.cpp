#include "Configuration.h"
#include <QSettings>

Configuration::Configuration() {
}

bool Configuration::load(const QString &configurationFilename) {
	QSettings settings(configurationFilename, QSettings::IniFormat);
	if(settings.status() == QSettings::NoError) {
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
