#include "ServerThreadManager.h"
#include "ServerThread.h"

ServerThreadManager::ServerThreadManager(
	QObject *parent
) : QObject(
	parent
) {
}

int ServerThreadManager::getCount() const {
	return serverThreadList.count();
}

bool ServerThreadManager::create(const qintptr clientSocketDescriptor) {
	ServerThread *serverThread = new ServerThread(
		serverThreadList,
		serverThreadMutex,
		this
	);
	if(serverThread) {
		connect(serverThread, &ServerThread::finished, serverThread, &ServerThread::ended);

		if(serverThread->initialize(clientSocketDescriptor))
			serverThread->start();

	} else {
		qDebug() << "Could not start thread";
		return false;
	}

	return true;
}
