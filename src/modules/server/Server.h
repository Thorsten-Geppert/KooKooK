#pragma once

#include <QTcpServer>
#include <QSslKey>
#include <QSslCertificate>
#include <QSocketNotifier>
#include <QHash>
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
		bool stop();
		void incomingConnection(qintptr clientSocketDescriptor) override;

		static void hupSignalHandler(int);
		static void termSignalHandler(int);

	private:
		ServerThreadManager serverThreadManager;
		RuntimeInformationType &rit;

		QHash<QString, QString> users;

		QSslKey sslKey;
		QSslCertificate sslCertificate;

		static int hupSignalFd[2];
		static int termSignalFd[2];

		QSocketNotifier *hupSocketNotifier;
		QSocketNotifier *termSocketNotifier;

		QTimer userTimer;

	public slots:
		void hupSignalSlot();
		void termSignalSlot();

	private slots:
		void userTimeout();
	
	signals:
		void exit(int status);

};
