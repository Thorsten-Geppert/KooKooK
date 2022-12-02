#pragma once

#include <QObject>
#include <QString>
#include "Configuration.h"

class RuntimeInformationType : public QObject {

	Q_OBJECT

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

	private:
		Configuration configuration;
		qint64 pid;

};
