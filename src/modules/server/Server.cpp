#include "Server.h"
#include <QTcpSocket>
#include <QSocketDescriptor>
#include <QDebug>
#include <sys/socket.h>
#include <unistd.h>

int Server::hupSignalFd[2] = { 0, 0 };
int Server::termSignalFd[2] = { 0, 0 };

Server::Server(
	RuntimeInformationType &rit,
	QObject *parent
) : QTcpServer(
	parent
), serverThreadManager(
	rit
), rit(
	rit
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

	// Test
	connect(&timer, &QTimer::timeout, this, &Server::timeout);
	timer.setInterval(5000);
	timer.setSingleShot(true);
	//timer.start();

	connect(this, &Server::newConnection, this, &Server::link);
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
	//serverThreadManager.create(clientSocketDescriptor);

	qDebug() << "incoming";

	QSslSocket *sslSocket = new QSslSocket(this);
	connect(sslSocket, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(sslErrors(QList<QSslError>)));

	SslConfigurationType::CacheStruct *cache = &rit.getConfiguration().getServer().getSsl().Cache;

	sslSocket->setSocketDescriptor(clientSocketDescriptor);
	sslSocket->setPrivateKey(cache->getKey());
	sslSocket->setLocalCertificate(cache->getCertificate());
	sslSocket->setPeerVerifyMode(QSslSocket::VerifyPeer);
	sslSocket->startServerEncryption();
}

void Server::link() {
	QTcpSocket *clientSocket = nextPendingConnection();
	connect(clientSocket, &QTcpSocket::readyRead, this, &Server::rx);
	connect(clientSocket, &QTcpSocket::disconnected, this, &Server::disconnected);
}

void Server::rx() {
	QTcpSocket* clientSocket = qobject_cast<QTcpSocket*>(sender());
	qDebug() << clientSocket->readAll();
	clientSocket->write("Server says Hello");
}

void Server::disconnected() {
	qDebug("Client Disconnected");
	QTcpSocket* clientSocket = qobject_cast<QTcpSocket*>(sender());
	clientSocket->deleteLater();
}

void Server::timeout() {
	qDebug() << "Thread count:" << serverThreadManager.getCount();
	serverThreadManager.stop();

	QThread::sleep(3);

	emit exit(0);
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

	qDebug() << "HUP signal";

	hupSocketNotifier->setEnabled(true);
}

void Server::termSignalSlot() {
	termSocketNotifier->setEnabled(false);

	char tmp;
	::read(termSignalFd[1], &tmp, sizeof(tmp));

	qDebug() << "TERM signal";
	stop();

	termSocketNotifier->setEnabled(true);
}

bool Server::stop() {
	rit.log("Stop emitted");

	const bool stopped = serverThreadManager.stop();

	QThread::sleep(rit.getConfiguration().getServer().getWaitSecondsAfterThreadsShutdown());
	emit exit(stopped ? 0 : 1);

	if(stopped)
		rit.log("Stop message: OK: Could shut down all processes (threads) correctly");
	else
		rit.log("Stop message: Error: Could not shut down all processes (threads) correctly", true);

	return stopped;
}

void Server::sslErrors(const QList<QSslError> &errors) {
	foreach (const QSslError &error, errors)
		qDebug() << error.errorString();
}
