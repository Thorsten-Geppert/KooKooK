#pragma once

#include <QString>
#include <QThreadStorage>
#include <QHash>
#include "Configuration.h"
#include "../../lib/Version.h"

class RuntimeInformationType {

	public:
		typedef QThreadStorage<QHash<QString, QString>> UserCacheType;

		RuntimeInformationType(const Version &version);

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

		UserCacheType &getUserCache();
		
		Version getVersion() const;

	private:
		Configuration configuration;
		qint64 pid = 0;
		UserCacheType userCache;
		Version version;

};
