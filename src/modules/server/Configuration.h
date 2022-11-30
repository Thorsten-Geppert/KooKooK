#pragma once

#include "lib/ServerConfigurationType.h"

class Configuration {

	public:
		Configuration();

		bool load(const QString &configurationFilename);

		void setServer(const ServerConfigurationType &server);
		ServerConfigurationType getServer() const;
	
	private:
		ServerConfigurationType server;

};

