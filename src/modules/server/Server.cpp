#include "Server.h"
#include <QTcpSocket>
#include <QDebug>

Server::Server(
	RuntimeInformationType &rit,
	QObject *parent
) : QTcpServer(
	parent
), rit(
	rit
) {
	connect(&timer, &QTimer::timeout, this, &Server::timeout);
	timer.setInterval(5000);
	timer.setSingleShot(true);
	timer.start();
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
