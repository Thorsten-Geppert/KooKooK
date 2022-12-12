#pragma once

#include <QTcpServer>
#include <QSslKey>
#include <QSslCertificate>
#include <QSocketNotifier>
#include "RuntimeInformationType.h"
#include "ProtocolList.h"

class Server : public QTcpServer {

	Q_OBJECT

	public:
		Server(
			RuntimeInformationType &rit,
			QObject *parent = nullptr
		);

		bool start();
		void stop();
		void incomingConnection(qintptr clientSocketDescriptor) override;

		static void hupSignalHandler(int);
		static void termSignalHandler(int);

	private:
		RuntimeInformationType &rit;
		ProtocolList protocolList;

		QSslKey sslKey;
		QSslCertificate sslCertificate;

		static int hupSignalFd[2];
		static int termSignalFd[2];

		QSocketNotifier *hupSocketNotifier;
		QSocketNotifier *termSocketNotifier;

	public slots:
		void hupSignalSlot();
		void termSignalSlot();
		void readyRead();
		void sslErrors(const QList<QSslError> &errors);
		void disconnected();

	signals:
		void exit(int status);

};
