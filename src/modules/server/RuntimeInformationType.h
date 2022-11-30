#pragma once

#include <QObject>
#include <QString>
#include "ConfigurationType.h"

class RuntimeInformationType : public QObject {

	Q_OBJECT

	public:
		RuntimeInformationType(
			const QString &configurationFilename
		);

		QString getConfigurationFilename() const;

		bool loadConfiguration(QString configurationFilename = "");

	private:
		QString configurationFilename;
		ConfigurationType configurationType;

		void setConfigurationFilename(const QString &configurationFilename);

};
