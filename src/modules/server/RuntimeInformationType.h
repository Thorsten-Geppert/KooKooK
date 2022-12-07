#pragma once

#include <QString>
#include "Configuration.h"

class RuntimeInformationType {

	public:
		RuntimeInformationType();

		Configuration::ErrorEnumeration loadConfiguration(const QString &configurationFilename);
		bool log(
			const QString &message,
			const bool error = false
		);

		Configuration &getConfiguration();

		void setPid(const qint64 pid);
		qint64 getPid() const;

		QSqlDatabase &getSqlDatabase();
		QSqlDatabase &getDb(); // Synonym for getSqlDatabase()

	private:
		Configuration configuration;
		qint64 pid = 0;

};
