#include "Server.h"
#include <QTcpSocket>
#include <QDebug>

Server::Server(
	QObject *parent
) : QTcpServer(
	parent
) {
	connect(&timer, &QTimer::timeout, this, &Server::timeout);
	timer.setInterval(1000);
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
}
