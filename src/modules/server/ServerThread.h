#pragma once

#include <QThread>
#include <QMutex>
#include <QList>
#include <QSslSocket>
#include <QSslError>
#include <QSharedPointer>
#include "RuntimeInformationType.h"
#include "Protocol.h"

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
		QSslSocket *clientSocket = nullptr;
		RuntimeInformationType &rit;
		QSharedPointer<Protocol> protocol;
		bool loggedIn = false;

		void setClientSocketDescriptor(const qintptr clientSocketDescriptor);
		void setLoggedIn(const bool loggedIn);
		bool isLoggedIn() const;

	public slots:
		void readyRead();
		void disconnected();
		void ended();
		void sslErrors(const QList<QSslError> &errors);

};
