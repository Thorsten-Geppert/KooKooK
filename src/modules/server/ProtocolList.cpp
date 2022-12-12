#include "ProtocolList.h"

ProtocolList::ProtocolList(
	const Version &version,
	const bool autoCleanup
) : QList<Protocol *>(
) {
	setVersion(version);
	setAutoCleanup(autoCleanup);
}

ProtocolList::~ProtocolList() {
	if(isAutoCleanup())
		qDeleteAll(*this);
}

void ProtocolList::setAutoCleanup(const bool autoCleanup) {
	this->autoCleanup = autoCleanup;
}

bool ProtocolList::isAutoCleanup() const {
	return autoCleanup;
}

Protocol *ProtocolList::createProtocol(QSslSocket *sslSocket) {
	if(!sslSocket)
		return nullptr;
	
	Protocol *protocol = getProtocol(sslSocket);
	if(!protocol)
		protocol = new Protocol(getVersion(), sslSocket);
	
	if(protocol)
		append(protocol);

	return protocol;
}

Protocol *ProtocolList::getProtocol(const QSslSocket *sslSocket) {
	if(!sslSocket)
		return nullptr;

	Protocol *protocol = nullptr;
	
	const int counter = count();
	for(int i = 0; i < counter; i++) {
		protocol = value(i);
		if(protocol && protocol->getSslSocket() == sslSocket)
			return protocol;
	}

	return nullptr;
}

void ProtocolList::removeProtocol(const QSslSocket *sslSocket) {
	if(sslSocket) {
		Protocol *protocol = getProtocol(sslSocket);
		if(protocol) {
			removeAll(protocol);
			delete protocol;
		}
	}
}

void ProtocolList::setVersion(const Version &version) {
	this->version = version;
}

Version ProtocolList::getVersion() const {
	return version;
}
