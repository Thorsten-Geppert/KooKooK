#include "SQLServerDatabaseConfigurationType.h"

SQLServerDatabaseConfigurationType::SQLServerDatabaseConfigurationType(
) : DatabaseConfigurationType(
) {
}

SQLServerDatabaseConfigurationType::SQLServerDatabaseConfigurationType(
	const QString &hostname,
	const QString &database,
	const QString &username,
	const QString &password,
	const int port
) : DatabaseConfigurationType(
) {
	setHostname(hostname);
	setDatabase(database);
	setUsername(username);
	setPassword(password);
	setPort(port);
}

void SQLServerDatabaseConfigurationType::setHostname(const QString &hostname) {
	this->hostname = hostname;
}

QString SQLServerDatabaseConfigurationType::getHostname() const {
	return hostname;
}

void SQLServerDatabaseConfigurationType::setDatabase(const QString &database) {
	this->database = database;
}

QString SQLServerDatabaseConfigurationType::getDatabase() const {
	return database;
}

void SQLServerDatabaseConfigurationType::setUsername(const QString &username) {
	this->username = username;
}

QString SQLServerDatabaseConfigurationType::getUsername() const {
	return username;
}

void SQLServerDatabaseConfigurationType::setPassword(const QString &password) {
	this->password = password;
}

QString SQLServerDatabaseConfigurationType::getPassword() const {
	return password;
}

void SQLServerDatabaseConfigurationType::setPort(const int port) {
	this->port = port;
}

int SQLServerDatabaseConfigurationType::getPort() const {
	return port;
}
