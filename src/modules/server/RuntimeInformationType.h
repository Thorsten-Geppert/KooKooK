#pragma once

#include <QObject>
#include <QString>
#include "Configuration.h"

class RuntimeInformationType : public QObject {

	Q_OBJECT

	public:
		RuntimeInformationType();

		bool loadConfiguration(const QString &configurationFilename);
		bool log(
			const QString &message,
			const bool error = false
		);

		Configuration &getConfiguration();

	private:
		Configuration configuration;

};
