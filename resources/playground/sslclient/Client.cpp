#include "Client.h"
#include <QSslKey>
#include <QSslCertificate>
#include <QSslConfiguration>
#include <QFile>
#include <QDebug>
#include "Configuration.h"
#include "../../../src/modules/lib/Version.h"
#include "../../../src/modules/server/Protocol.h"

Client::Client() {
	QSslCertificate sslCertificate;
	QFile certificateFile(CA_CERTIFICATE);
	if(certificateFile.open(QIODevice::ReadOnly)) {
		sslCertificate = QSslCertificate(certificateFile.readAll());
		certificateFile.close();
	} else {
		qDebug() << "Could not load ca certificate file";
	}

	QSslConfiguration sslConfiguration = QSslConfiguration::defaultConfiguration();
	sslConfiguration.addCaCertificates(QList<QSslCertificate>() << sslCertificate);
	QSslConfiguration::setDefaultConfiguration(sslConfiguration);

	connect(&clientSocket, &QSslSocket::readyRead, this, &Client::readyRead);
	connect(&clientSocket, &QSslSocket::disconnected, this, &Client::disconnect);
	connect(&clientSocket, &QSslSocket::sslErrors, this, &Client::sslErrors);

	clientSocket.setPrivateKey(PRIVATE_KEY);
	clientSocket.setLocalCertificate(LOCALE_CERTIFICATE);

	clientSocket.setPeerVerifyMode(VERIFY ? QSslSocket::VerifyPeer: QSslSocket::VerifyNone);
}

bool Client::connectToServer() {
	clientSocket.connectToHostEncrypted(HOSTNAME, PORT);

	if(clientSocket.waitForEncrypted(10000)) {
		return true;
	}

	return false;
}

void Client::sslErrors(const QList<QSslError> &errors) {
	foreach(const QSslError &error, errors)
		qDebug() << error.errorString();
}

void Client::disconnect() {
	qDebug("Server disconnected");
	emit disconnected();
}

void Client::readyRead() {
	qDebug() << clientSocket.readAll();
}
