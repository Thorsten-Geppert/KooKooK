#pragma once

#include <QThread>
#include <QMutex>
#include <QPointer>
#include <QTcpSocket>
#include "RuntimeInformationType.h"

class ServerThreadList;
class ServerThread : public QThread {

	Q_OBJECT

	public:
		ServerThread(
			RuntimeInformationType &rit,
			ServerThreadList &serverThreadList,
			QMutex &serverThreadMutex,
			QObject *parent = nullptr
		);

		bool initialize(const qintptr clientSocketDescriptor);

		void run() override;

		qintptr getClientSocketDescriptor() const;

	private:
		ServerThreadList &serverThreadList;
		QMutex &serverThreadMutex;
		qintptr clientSocketDescriptor = -1;
		QPointer<QTcpSocket> clientSocket = nullptr;
		RuntimeInformationType &rit;

		void setClientSocketDescriptor(const qintptr clientSocketDescriptor);

	public slots:
		void readyRead();
		void disconnected();
		void ended();

};
