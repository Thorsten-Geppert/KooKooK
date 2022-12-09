#include "ServerThread.h"
#include <QMutexLocker>
#include "ServerThreadList.h"
#include "../lib/Version.h"

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
	connect(clientSocket, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(sslErrors(QList<QSslError>)));
	if(!clientSocket->setSocketDescriptor(clientSocketDescriptor)) {
		rit.log(QString("Could not set socket descriptor: %1").arg(clientSocket->errorString()));

		return false;
	}

	SslConfigurationType::CacheStruct *cache = &rit.getConfiguration().getServer().getSsl().Cache;

	clientSocket->setPrivateKey(cache->getKey());
	clientSocket->setLocalCertificate(cache->getCertificate());
	clientSocket->setPeerVerifyMode(cache->getVerify());
	clientSocket->startServerEncryption();

	return true;
}

void ServerThread::run() {
	if(clientSocket) {
		connect(clientSocket, &QTcpSocket::readyRead, this, &ServerThread::readyRead);
		connect(clientSocket, &QTcpSocket::disconnected, this, &ServerThread::disconnected);

		Version version(0, 0, 1);
		protocol = QSharedPointer<Protocol>(new Protocol(version, *clientSocket));

		protocol->askWelcomeMessage();

		exec();
	}
	qDebug() << "End Thread";
}

void ServerThread::setClientSocketDescriptor(const qintptr clientSocketDescriptor) {
	this->clientSocketDescriptor = clientSocketDescriptor;
}

qintptr ServerThread::getClientSocketDescriptor() const {
	return clientSocketDescriptor;
}

void ServerThread::readyRead() {
	QByteArray received = clientSocket->readAll();

	Packet::ErrorType errorType = Packet::ErrorType::NONE;

	Packet packet = Protocol::createPacket(received, &errorType);
	if(errorType == Packet::ErrorType::NONE) {
		// Authenticate
		if(packet.isCommand("Authenticate")) {
			rit.log("Authenticate initiated");

			bool sent = false;
			QString username;

			Protocol::LoginErrorType loginErrorType = protocol->endWelcomeMessage(
				rit.getUserCache(),
				packet.getData(),
				sent,
				&username
			);

			if(loginErrorType == Protocol::LoginErrorType::LOGGED_IN && sent) {
				rit.log(QString("The user '%1' is logged in successfully").arg(username));
				setLoggedIn(true);
			} else {
				rit.log(QString("The user '%1' is not logged in: %2 (Sent: %3)").arg(username, Protocol::loginErrorTypeToString(loginErrorType), sent ? "YES" : "NO"), true);
				setLoggedIn(false);
			}

		// Unknown command
		} else {
			rit.log(QString("Unknown command '%1'").arg(packet.getCommand()), true);
		}
	} else {
		rit.log(QString("Error: %1").arg(Packet::errorTypeToString(errorType)), true);
	}
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
	qDebug() << "SSL error";
	foreach (const QSslError &error, errors)
		qDebug() << error.errorString();
}

void ServerThread::setLoggedIn(const bool loggedIn) {
	this->loggedIn = loggedIn;
}

bool ServerThread::isLoggedIn() const {
	return loggedIn;
}
