#pragma once

#include <QSslSocket>
#include "../../../src/modules/lib/ClientSslSocket.h"

class Client : public QObject {

	Q_OBJECT

	public:
		Client();

		bool connectToServer(const int count = 1);

	private slots:
		void sslErrors(const QList<QSslError> &errors);
		void readyRead();
		void disconnect();

	signals:
		void disconnected();

};
