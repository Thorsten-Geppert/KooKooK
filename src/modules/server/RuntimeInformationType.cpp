#include "RuntimeInformationType.h"

RuntimeInformationType::RuntimeInformationType(
) {
}

bool RuntimeInformationType::loadConfiguration(const QString &configurationFilename) {
	return configuration.load(configurationFilename);
}

bool RuntimeInformationType::log(
	const QString &message,
	const bool error
) {
	return configuration.log(message, error);
}

Configuration &RuntimeInformationType::getConfiguration() {
	return configuration;
}
