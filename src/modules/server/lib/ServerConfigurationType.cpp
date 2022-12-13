#include "ServerConfigurationType.h"

ServerConfigurationType::ServerConfigurationType(
) : ConfigurationType(
) {
}

ServerConfigurationType::ServerConfigurationType(
	const QString &hostname,
	const quint16 port
) : ConfigurationType(
) {
	setHostname(hostname);
	setPort(port);
}

void ServerConfigurationType::setHostname(const QString &hostname) {
	this->hostname = hostname;
}

QString ServerConfigurationType::getHostname() const {
	return hostname;
}

void ServerConfigurationType::setPort(const quint16 port) {
	this->port = port;
}

quint16 ServerConfigurationType::getPort() const {
	return port;
}

SslConfigurationType &ServerConfigurationType::getSsl() {
	return sslConfigurationType;
}
