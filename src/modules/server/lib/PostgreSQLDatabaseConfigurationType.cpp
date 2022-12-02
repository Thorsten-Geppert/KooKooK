#include "PostgreSQLDatabaseConfigurationType.h"

PostgreSQLDatabaseConfigurationType::PostgreSQLDatabaseConfigurationType(
) : SQLServerDatabaseConfigurationType(
) {
}

PostgreSQLDatabaseConfigurationType::PostgreSQLDatabaseConfigurationType(
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

QSqlDatabase PostgreSQLDatabaseConfigurationType::create() {
	QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");

	db.setHostName(getHostname());
	db.setDatabaseName(getDatabase());
	db.setUserName(getUsername());
	db.setPassword(getPassword());
	db.setPort(getPort());

	return db;
}
