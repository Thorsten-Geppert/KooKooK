#include "RuntimeInformationType.h"
#include <QSettings>

RuntimeInformationType::RuntimeInformationType(
	const QString &configurationFilename
) {
	setConfigurationFilename(configurationFilename);
}

void RuntimeInformationType::setConfigurationFilename(
	const QString &configurationFilename
) {
	this->configurationFilename = configurationFilename;
}

QString RuntimeInformationType::getConfigurationFilename() const {
	return configurationFilename;
}

bool RuntimeInformationType::loadConfiguration(QString configurationFilename) {
	if(configurationFilename.isEmpty())
		configurationFilename = getConfigurationFilename();

	QSettings settings(
		configurationFilename,
		QSettings::IniFormat
	);

	if(settings.status() == QSettings::NoError) {
		return true;
	}

	return false;
}
