#include "ServerThreadManager.h"
#include "ServerThread.h"
#include <QTime>

ServerThreadManager::ServerThreadManager(
	RuntimeInformationType &rit,
	QObject *parent
) : QObject(
	parent
), rit(
	rit
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
		rit.log("Could not start thread", true);

		return false;
	}

	rit.log(QString("New server thread started (Thread count: %1)").arg(getCount()), true);

	return true;
}

bool ServerThreadManager::stop(
	unsigned int *quittedThreadCount,
	unsigned int *terminatedThreadCount
) {
	ServerThread *serverThread = nullptr;
	const int serverThreadCount = serverThreadList.count();
	for(int i = 0; i < serverThreadCount; i++) {
		serverThread = serverThreadList.value(i);
		if(serverThread) {
			rit.log(QString("Try to stop thread number %1").arg(i));
			serverThread->quit();
		}
	}
	
	// Wait until threads are finished
	QThread::sleep(10);

	unsigned int terminated = 0;
	for(int i = 0; i < serverThreadList.count(); i++) {
		serverThread = serverThreadList.value(i);
		if(serverThread) {
			rit.log(QString("Try to terminate thread number %1").arg(i));
			serverThread->terminate();
			terminated++;
		}
	}
	
	// Wait until threads are terminated
	if(terminated > 0)
		QThread::sleep(10);

	if(quittedThreadCount)
		*quittedThreadCount = serverThreadCount - terminated;
	if(terminatedThreadCount)
		*terminatedThreadCount = terminated;
	
	return terminated != 0;
}
