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
}

bool Server::start() {
	const auto hostname = rit.getConfiguration().getServer().getHostname();
	const auto port = rit.getConfiguration().getServer().getPort();
	if(!listen(QHostAddress(hostname), port)) {
		rit.log(QString("Starting server error (%1:%2): %3").arg(hostname).arg(port).arg(errorString()), true);
		return false;
	}

	rit.log(QString("Starting server ok (%1:%2)").arg(hostname).arg(port));

	return true;
}

// TODO implement me
void Server::incomingConnection(qintptr clientSocketDescriptor) {
	serverThreadManager.create(clientSocketDescriptor);
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
