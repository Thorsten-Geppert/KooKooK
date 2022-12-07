#pragma once

#include <QSslSocket>

class Client : public QObject {

	Q_OBJECT

	public:
		Client();

		bool connectToServer();

	private:
		QSslSocket clientSocket;

	private slots:
		void sslErrors(const QList<QSslError> &errors);
		void readyRead();
		void disconnect();

	signals:
		void disconnected();

};
