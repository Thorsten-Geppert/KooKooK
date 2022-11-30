#include "Server.h"
#include <QTcpSocket>
#include <QDebug>

Server::Server(
	QObject *parent
) : QTcpServer(
	parent
) {
	connect(&timer, &QTimer::timeout, this, &Server::timeout);
	timer.setInterval(5000);
	timer.setSingleShot(true);
	timer.start();
}

bool Server::start() {
	// TODO parameter configuration
	if(!listen(QHostAddress::AnyIPv4, 12345)) {
		qDebug() << errorString();
		return false;
	}

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
