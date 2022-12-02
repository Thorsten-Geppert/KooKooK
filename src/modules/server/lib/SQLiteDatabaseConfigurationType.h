#pragma once

#include "SQLServerDatabaseConfigurationType.h"

class SQLiteDatabaseConfigurationType : public SQLServerDatabaseConfigurationType {

	public:
		SQLiteDatabaseConfigurationType();
		SQLiteDatabaseConfigurationType(const QString &database);

		// Delete what we don't need
		SQLiteDatabaseConfigurationType(
			const QString &hostname,
			const QString &database,
			const QString &username,
			const QString &password,
			const int port = 3306
		) = delete;

		void setHostname(const QString &hostname) = delete;
		QString getHostname() const = delete;

		void setUsername(const QString &username) = delete;
		QString getUsername() const = delete;

		void setPassword(const QString &password) = delete;
		QString getPassword() const = delete;

		void setPort(const int port) = delete;
		int getPort() const = delete;

		virtual QSqlDatabase create() override;

};

