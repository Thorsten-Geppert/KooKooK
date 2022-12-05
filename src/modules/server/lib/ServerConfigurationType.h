#pragma once

#include "ConfigurationType.h"
#include <QString>

class ServerConfigurationType : public ConfigurationType {
	
	public:
		ServerConfigurationType();
		ServerConfigurationType(
			const QString &hostname,
			const quint16 port,
			const unsigned int threads
		);

		void setHostname(const QString &hostname);
		QString getHostname() const;

		void setPort(const quint16 port);
		quint16 getPort() const;
		
		void setWaitSecondsAfterThreadsShutdown(const unsigned long waitSecondsAfterThreadsShutdown);
		unsigned long getWaitSecondsAfterThreadsShutdown() const;

		void setThreads(const unsigned int threads);
		unsigned int getThreads() const;
	
	private:
		QString hostname;
		quint16 port = 0;
		unsigned long waitSecondsAfterThreadsShutdown = 5;
		unsigned int threads = 10;

};
