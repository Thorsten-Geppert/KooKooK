#pragma once

#include "DatabaseConfigurationType.h"

class SQLServerDatabaseConfigurationType : public DatabaseConfigurationType {

	public:
		SQLServerDatabaseConfigurationType();
		SQLServerDatabaseConfigurationType(
			const QString &hostname,
			const QString &database,
			const QString &username,
			const QString &password,
			const int port
		);

		void setHostname(const QString &hostname);
		QString getHostname() const;

		void setDatabase(const QString &database);
		QString getDatabase() const;

		void setUsername(const QString &username);
		QString getUsername() const;

		void setPassword(const QString &password);
		QString getPassword() const;

		void setPort(const int port);
		int getPort() const;
	
	protected:
		QString hostname;
		QString database;
		QString username;
		QString password;
		int port = 0;

};
