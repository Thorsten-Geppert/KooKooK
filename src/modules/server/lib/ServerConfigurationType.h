#pragma once

#include "ConfigurationType.h"
#include <QString>

class ServerConfigurationType : public ConfigurationType {
	
	public:
		ServerConfigurationType();
		ServerConfigurationType(
			const QString &hostname,
			const quint16 port
		);

		void setHostname(const QString &hostname);
		QString getHostname() const;

		void setPort(const quint16 port);
		quint16 getPort() const;
	
	private:
		QString hostname;
		quint16 port;

};
