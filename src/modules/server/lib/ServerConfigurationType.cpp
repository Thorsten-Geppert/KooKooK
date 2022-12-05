#include "ServerConfigurationType.h"

ServerConfigurationType::ServerConfigurationType(
) : ConfigurationType(
) {
}

ServerConfigurationType::ServerConfigurationType(
	const QString &hostname,
	const quint16 port,
	const unsigned int threads
) : ConfigurationType(
) {
	setHostname(hostname);
	setPort(port);
	setThreads(threads);
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

void ServerConfigurationType::setWaitSecondsAfterThreadsShutdown(const unsigned long waitSecondsAfterThreadsShutdown) {
	this->waitSecondsAfterThreadsShutdown = waitSecondsAfterThreadsShutdown;
}

unsigned long ServerConfigurationType::getWaitSecondsAfterThreadsShutdown() const {
	return waitSecondsAfterThreadsShutdown;
}

void ServerConfigurationType::setThreads(const unsigned int threads) {
	this->threads = threads;
}

unsigned int ServerConfigurationType::getThreads() const {
	return threads;
}
