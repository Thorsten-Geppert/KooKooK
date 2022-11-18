#pragma once

#include <QTcpServer>
#include "ServerThreadManager.h"

#include <QTimer>

class Server : public QTcpServer {

	Q_OBJECT

	public:
		Server(QObject *parent = nullptr);

		bool start();

		void incomingConnection(qintptr clientSocketDescriptor) override;
	
	private:
		ServerThreadManager serverThreadManager;

		QTimer timer;

	private slots:
		void timeout();

};
