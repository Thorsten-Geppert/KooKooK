#include "SQLiteDatabaseConfigurationType.h"

SQLiteDatabaseConfigurationType::SQLiteDatabaseConfigurationType(
) : SQLServerDatabaseConfigurationType(
) {
}

SQLiteDatabaseConfigurationType::SQLiteDatabaseConfigurationType(
	const QString &database
) : SQLServerDatabaseConfigurationType(
) {
	setDatabase(database);
}

QSqlDatabase SQLiteDatabaseConfigurationType::create() {
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName(getDatabase());
	return db;
}
