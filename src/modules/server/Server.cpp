#include "Server.h"
#include <QTcpSocket>
#include <QSocketDescriptor>
#include <QDebug>
#include <sys/socket.h>
#include <unistd.h>
#include "Protocol.h"

int Server::hupSignalFd[2] = { 0, 0 };
int Server::termSignalFd[2] = { 0, 0 };

Server::Server(
	RuntimeInformationType &rit,
	QObject *parent
) : QTcpServer(
	parent
), rit(
	rit
), protocolList(
	rit.getVersion()
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

void Server::incomingConnection(qintptr clientSocketDescriptor) {
	QSslSocket *clientSocket = new QSslSocket(this);
	//clientSockets.append(clientSocket);

	connect(clientSocket, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(sslErrors(QList<QSslError>)));
	if(!clientSocket->setSocketDescriptor(clientSocketDescriptor)) {
		rit.log(QString("Could not set socket descriptor: %1").arg(clientSocket->errorString()));
	} else {
		SslConfigurationType::CacheStruct *cache = &rit.getConfiguration().getServer().getSsl().Cache;

		clientSocket->setPrivateKey(cache->getKey());
		clientSocket->setLocalCertificate(cache->getCertificate());
		clientSocket->setPeerVerifyMode(cache->getVerify());
		clientSocket->startServerEncryption();

		connect(clientSocket, &QTcpSocket::readyRead, this, &Server::readyRead);
		connect(clientSocket, &QTcpSocket::disconnected, this, &Server::disconnected);

		Protocol *protocol = protocolList.createProtocol(clientSocket);
		if(protocol) {
			protocol->askWelcomeMessage();
		} else {
			// TODO Alles abbrechen
			rit.log("Could not create protocol by socket", true);
		}
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
	QSslSocket *clientSocket = qobject_cast<QSslSocket *>(sender());

	QByteArray received = clientSocket->readAll();

	Packet::ErrorType errorType = Packet::ErrorType::NONE;

	Packet packet = Protocol::createPacket(received, &errorType);
	if(errorType == Packet::ErrorType::NONE) {
		// Authenticate
		if(packet.isCommand("Authenticate")) {
			rit.log("Authenticate initiated");

			bool sent = false;
			QString username;

			Protocol *protocol = protocolList.getProtocol(clientSocket);
			// TODO Alles abbrechen
			if(protocol) {
				Protocol::LoginErrorType loginErrorType = protocol->endWelcomeMessage(
					rit.getUserCache(),
					packet.getData(),
					sent,
					&username
				);

				if(loginErrorType == Protocol::LoginErrorType::LOGGED_IN && sent) {
					rit.log(QString("The user '%1' is logged in successfully").arg(username));
				} else {
					rit.log(QString("The user '%1' is not logged in: %2 (Sent: %3)").arg(username, Protocol::loginErrorTypeToString(loginErrorType), sent ? "YES" : "NO"), true);
				}
			} else {
				rit.log("Could not find protocol by socket", true);
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
