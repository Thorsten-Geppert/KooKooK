#include "MySQLDatabaseConfigurationType.h"

MySQLDatabaseConfigurationType::MySQLDatabaseConfigurationType(
) : SQLServerDatabaseConfigurationType(
) {
}

MySQLDatabaseConfigurationType::MySQLDatabaseConfigurationType(
	const QString &hostname,
	const QString &database,
	const QString &username,
	const QString &password,
	const int port
) : SQLServerDatabaseConfigurationType(
	hostname,
	database,
	username,
	password,
	port
) {
}

QSqlDatabase MySQLDatabaseConfigurationType::create() {
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

	db.setHostName(getHostname());
	db.setDatabaseName(getDatabase());
	db.setUserName(getUsername());
	db.setPassword(getPassword());
	db.setPort(getPort());

	return db;
}
