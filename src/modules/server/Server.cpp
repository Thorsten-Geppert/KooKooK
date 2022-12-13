#include "Server.h"
#include <QTcpSocket>
#include <QSocketDescriptor>
#include <QDebug>
#include <sys/socket.h>
#include <unistd.h>
#include "../lib/SslSocket.h"

int Server::hupSignalFd[2] = { 0, 0 };
int Server::termSignalFd[2] = { 0, 0 };

Server::Server(
	RuntimeInformationType &rit,
	QObject *parent
) : QTcpServer(
	parent
), rit(
	rit
), serverSslSocketList(
	rit.getDb(),
	rit.getVersion(),
	this
) {
	// Signal handling
	if(::socketpair(AF_UNIX, SOCK_STREAM, 0, hupSignalFd))
		qFatal("Couldn't create HUP socketpair");
	
	if(::socketpair(AF_UNIX, SOCK_STREAM, 0, termSignalFd))
		qFatal("Couldn't create TERM socketpair");
	
	hupSocketNotifier = new QSocketNotifier(hupSignalFd[1], QSocketNotifier::Read, this);
	connect(hupSocketNotifier, SIGNAL(activated(QSocketDescriptor)), this, SLOT(hupSignalSlot()));

	termSocketNotifier = new QSocketNotifier(termSignalFd[1], QSocketNotifier::Read, this);
	connect(termSocketNotifier, SIGNAL(activated(QSocketDescriptor)), this, SLOT(termSignalSlot()));
}

bool Server::start() {
	auto &serverConfiguration = rit.getConfiguration().getServer();
	const auto hostname = serverConfiguration.getHostname();
	const auto port = serverConfiguration.getPort();

	if(!listen(QHostAddress(hostname), port)) {
		rit.log(QString("Starting server error (%1:%2): %3").arg(hostname).arg(port).arg(errorString()), true);
		return false;
	}

	rit.log(QString("Starting server ok (%1:%2)").arg(hostname).arg(port));

	return true;
}

void Server::incomingConnection(qintptr serverSocketDescriptor) {
	ServerSslSocket *serverSocket = serverSslSocketList.add();

	connect(serverSocket, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(sslErrors(QList<QSslError>)));
	if(!serverSocket->setSocketDescriptor(serverSocketDescriptor)) {
		rit.log(QString("Could not set socket descriptor: %1").arg(serverSocket->errorString()));
	} else {
		SslConfigurationType::CacheStruct *cache = &rit.getConfiguration().getServer().getSsl().Cache;

		serverSocket->setPrivateKey(cache->getKey());
		serverSocket->setLocalCertificate(cache->getCertificate());
		serverSocket->setPeerVerifyMode(cache->getVerify());
		serverSocket->startServerEncryption();

		connect(serverSocket, &QTcpSocket::readyRead, this, &Server::readyRead);
		connect(serverSocket, &QTcpSocket::disconnected, this, &Server::disconnected);

		serverSocket->askWelcomeMessage();
	}
}

void Server::hupSignalHandler(int) {
	char a = 1;
	::write(hupSignalFd[0], &a, sizeof(a));
}

void Server::termSignalHandler(int) {
	char a = 1;
	::write(termSignalFd[0], &a, sizeof(a));
}

void Server::hupSignalSlot() {
	hupSocketNotifier->setEnabled(false);

	char tmp;
	::read(hupSignalFd[1], &tmp, sizeof(tmp));

	hupSocketNotifier->setEnabled(true);
}

void Server::termSignalSlot() {
	termSocketNotifier->setEnabled(false);

	char tmp;
	::read(termSignalFd[1], &tmp, sizeof(tmp));

	stop();

	termSocketNotifier->setEnabled(true);
}

void Server::stop() {
	rit.log("Stop emitted");
}

void Server::readyRead() {
	ServerSslSocket *serverSocket = serverSslSocketList.cast(sender());

	QByteArray received = serverSocket->readAll();

	Packet::ErrorType errorType = Packet::ErrorType::NONE;

	Packet packet = SslSocket::createPacket(received, &errorType);
	if(errorType == Packet::ErrorType::NONE) {
		// Authenticate
		if(packet.isCommand("Authenticate")) {
			rit.log("Authenticate initiated");

			bool sent = false;
			QString username;

			// TODO Alles abbrechen
			ServerSslSocket::LoginErrorType loginErrorType = serverSocket->endWelcomeMessage(
				packet.getData(),
				sent,
				&username
			);

			if(loginErrorType == ServerSslSocket::LoginErrorType::LOGGED_IN && sent) {
				rit.log(QString("The user '%1' is logged in successfully").arg(username));
			} else {
				rit.log(QString("The user '%1' is not logged in: %2 (Sent: %3)").arg(username, SslSocket::loginErrorTypeToString(loginErrorType), sent ? "YES" : "NO"), true);
			}

		// Unknown command
		} else {
			rit.log(QString("Unknown command '%1'").arg(packet.getCommand()), true);
		}
	} else {
		rit.log(QString("Error: %1").arg(Packet::errorTypeToString(errorType)), true);
	}
}

void Server::sslErrors(const QList<QSslError> &errors) {
	qDebug() << "SSL error";
	foreach (const QSslError &error, errors)
		qDebug() << error.errorString();
}

void Server::disconnected() {
	qDebug() << "Socket disconnect";
}
