#pragma once

#include "SQLServerDatabaseConfigurationType.h"

class MySQLDatabaseConfigurationType : public SQLServerDatabaseConfigurationType {

	public:
		MySQLDatabaseConfigurationType();
		MySQLDatabaseConfigurationType(
			const QString &hostname,
			const QString &database,
			const QString &username,
			const QString &password,
			const int port = 5432
		);

		virtual QSqlDatabase create() override;

};
