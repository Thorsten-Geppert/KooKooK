#include "ServerThread.h"
#include <QMutexLocker>
#include "ServerThreadList.h"

ServerThread::ServerThread(
	RuntimeInformationType &rit,
	ServerThreadList &serverThreadList,
	QMutex &serverThreadMutex,
	QObject *parent
) : QThread(
	parent
), serverThreadList(
	serverThreadList
), serverThreadMutex(
	serverThreadMutex
), rit(
	rit
) {
	QMutexLocker serverThreadMutexLocker(&serverThreadMutex);
	serverThreadList.append(this);
}

bool ServerThread::initialize(const qintptr clientSocketDescriptor) {
	setClientSocketDescriptor(clientSocketDescriptor);

	clientSocket = new QSslSocket(this);
	if(!clientSocket->setSocketDescriptor(clientSocketDescriptor)) {
		rit.log(QString("Could not set socket descriptor: %1").arg(clientSocket->errorString()));

		return false;
	}

	SslConfigurationType::CacheStruct *cache = &rit.getConfiguration().getServer().getSsl().Cache;

	clientSocket->setPrivateKey(cache->getKey());
	clientSocket->setLocalCertificate(cache->getCertificate());
	clientSocket->setPeerVerifyMode(QSslSocket::VerifyPeer);
	clientSocket->startServerEncryption();

	return true;
}

void ServerThread::run() {
	if(clientSocket) {
		//connect(clientSocket, &QTcpSocket::readyRead, this, &ServerThread::readyRead);
		//connect(clientSocket, &QTcpSocket::disconnected, this, &ServerThread::disconnected);
		//connect(clientSocket, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(sslErrors(QList<QSslError>)));
		
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

void ServerThread::sslErrors(const QList<QSslError> &errors) {
	foreach (const QSslError &error, errors)
		qDebug() << error.errorString();
}
