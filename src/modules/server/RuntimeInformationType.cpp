#include "RuntimeInformationType.h"

RuntimeInformationType::RuntimeInformationType(
) {
}

Configuration::ErrorEnumeration RuntimeInformationType::loadConfiguration(const QString &configurationFilename) {
	return configuration.load(configurationFilename);
}

bool RuntimeInformationType::log(
	const QString &message,
	const bool error
) {
	return configuration.log(message, error, getPid());
}

Configuration &RuntimeInformationType::getConfiguration() {
	return configuration;
}

void RuntimeInformationType::setPid(const qint64 pid) {
	this->pid = pid;
}

qint64 RuntimeInformationType::getPid() const {
	return pid;
}
