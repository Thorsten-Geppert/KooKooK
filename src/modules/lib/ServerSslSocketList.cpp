#include "ServerSslSocketList.h"

ServerSslSocketList::ServerSslSocketList(
	QSqlDatabase &db,
	const Version &version,
	QObject *parent,
	const bool autoCleanup
) : QList<ServerSslSocket *>(
), db(
	db
) {
	setVersion(version);
	setParent(parent);
	setAutoCleanup(autoCleanup);	
}

ServerSslSocketList::~ServerSslSocketList() {
	if(isAutoCleanup())
		qDeleteAll(*this);
}

void ServerSslSocketList::setParent(QObject *parent) {
	this->parent = parent;
}

QObject *ServerSslSocketList::getParent() {
	return parent;
}

void ServerSslSocketList::setAutoCleanup(const bool autoCleanup) {
	this->autoCleanup = autoCleanup;
}

bool ServerSslSocketList::isAutoCleanup() const {
	return autoCleanup;
}

void ServerSslSocketList::setVersion(const Version &version) {
	this->version = version;
}

Version ServerSslSocketList::getVersion() const {
	return version;
}

ServerSslSocket *ServerSslSocketList::add() {
	ServerSslSocket *serverSslSocket = new ServerSslSocket(getDb(), getVersion(), getParent());
	append(serverSslSocket);
	return serverSslSocket;
}

ServerSslSocket *ServerSslSocketList::cast(QObject *serverSslSocket) {
	return qobject_cast<ServerSslSocket *>(serverSslSocket);
}

QSqlDatabase &ServerSslSocketList::getDb() {
	return db;
}
