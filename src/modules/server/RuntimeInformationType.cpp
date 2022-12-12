#include "RuntimeInformationType.h"

RuntimeInformationType::RuntimeInformationType(
	const Version &version
) {
	this->version = version;
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

QSqlDatabase &RuntimeInformationType::getSqlDatabase() {
	return configuration.getSqlDatabase();
}

QSqlDatabase &RuntimeInformationType::getDb() {
	return configuration.getSqlDatabase();
}

RuntimeInformationType::UserCacheType &RuntimeInformationType::getUserCache() {
	return userCache;
}

Version RuntimeInformationType::getVersion() const {
	return version;
}
