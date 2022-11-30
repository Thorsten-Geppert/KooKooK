#include "ServerThread.h"
#include <QMutexLocker>
#include "ServerThreadList.h"

ServerThread::ServerThread(
	ServerThreadList &serverThreadList,
	QMutex &serverThreadMutex,
	QObject *parent
) : QThread(
	parent
), serverThreadList(
	serverThreadList
), serverThreadMutex(
	serverThreadMutex
) {
	QMutexLocker serverThreadMutexLocker(&serverThreadMutex);
	serverThreadList.append(this);
}

bool ServerThread::initialize(const qintptr clientSocketDescriptor) {
	setClientSocketDescriptor(clientSocketDescriptor);

	clientSocket = new QTcpSocket;
	if(!clientSocket->setSocketDescriptor(clientSocketDescriptor)) {
		qDebug() << clientSocket->errorString();

		return false;
	}

	return true;
}

void ServerThread::run() {
	if(clientSocket) {
		connect(clientSocket, &QTcpSocket::readyRead, this, &ServerThread::readyRead);
		connect(clientSocket, &QTcpSocket::disconnected, this, &ServerThread::disconnected);
	}

	exec();

	// Quit thread
	qDebug() << "end";
}

void ServerThread::setClientSocketDescriptor(const qintptr clientSocketDescriptor) {
	this->clientSocketDescriptor = clientSocketDescriptor;
}

qintptr ServerThread::getClientSocketDescriptor() const {
	return clientSocketDescriptor;
}

void ServerThread::readyRead() {
	QByteArray data = clientSocket->readAll();
	clientSocket->write(data);
}

void ServerThread::disconnected() {
	exit(0);
}

void ServerThread::ended() {
	QMutexLocker serverThreadMutexLocker(&serverThreadMutex);
	serverThreadList.removeAll(this);

	deleteLater();
}
