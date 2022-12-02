#pragma once

#include "SQLServerDatabaseConfigurationType.h"

class PostgreSQLDatabaseConfigurationType : public SQLServerDatabaseConfigurationType {

	public:
		PostgreSQLDatabaseConfigurationType();
		PostgreSQLDatabaseConfigurationType(
			const QString &hostname,
			const QString &database,
			const QString &username,
			const QString &password,
			const int port
		);

		virtual QSqlDatabase create() override;

};
