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

		void run() override;

		int getSocketCount() const;

	private:
		ServerThreadList &serverThreadList;
		QMutex &serverThreadMutex;
		RuntimeInformationType &rit;
		QSharedPointer<Protocol> protocol;
		QList<QSslSocket *> clientSockets;

	public slots:
		void readyRead();
		void disconnected();
		void ended();
		void sslErrors(const QList<QSslError> &errors);
		void initialize(const qintptr clientSocketDescriptor);

};
