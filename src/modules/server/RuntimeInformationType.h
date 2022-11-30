#pragma once

#include <QObject>
#include <QString>
#include "Configuration.h"

class RuntimeInformationType : public QObject {

	Q_OBJECT

	public:
		RuntimeInformationType();

		bool loadConfiguration(const QString &configurationFilename);

	private:
		Configuration configuration;

};
