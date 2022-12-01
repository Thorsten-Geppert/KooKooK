#pragma once

#include <QTcpServer>
#include "ServerThreadManager.h"
#include "RuntimeInformationType.h"

#include <QTimer>

class Server : public QTcpServer {

	Q_OBJECT

	public:
		Server(
			RuntimeInformationType &rit,
			QObject *parent = nullptr
		);

		bool start();
		void incomingConnection(qintptr clientSocketDescriptor) override;
	
	private:
		ServerThreadManager serverThreadManager;
		RuntimeInformationType &rit;

		QTimer timer;

	private slots:
		void timeout();
	
	signals:
		void exit(int status);

};
