#include "Client.h"
#include <QSslKey>
#include <QSslCertificate>
#include <QSslConfiguration>
#include <QFile>
#include <QDebug>
#include "Configuration.h"
#include "../../../src/modules/lib/Version.h"
#include "../../../src/modules/lib/Packet.h"
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
	const QByteArray received = clientSocket.readAll();

	Packet packet;
	const Packet::ErrorType errorType = packet.parse(received);
	if(errorType == Packet::ErrorType::NONE) {
		qDebug() << "RECEIVED:" << packet.toByteArray();

		if(packet.isCommand("Authenticate")) {
			Version version;
			QUuid uuid;

			if(Protocol::parseAuthenticationString(packet.getData(), version, uuid)) {
				qDebug() << "Version:" << version.toString();
				qDebug() << "UUID:" << uuid.toString();

				Protocol protocol(version, clientSocket);
				if(protocol.answerWelcomeMessage(uuid, "user2", "password2")) {
					qDebug() << "Send welcome message is ok";
				} else {
					qDebug() << "Send welcome message is not ok";
				}
			} else {
				qDebug() << "Could not parse authentication string";
			}
		} else if(packet.isCommand("Authenticated")) {
			qDebug() << "Authenticated (or not)!" << packet.toByteArray();
			if(packet.getData() == "OK")
				qDebug() << "LOGGED IN";
			else
				qDebug() << "NOT LOGGED IN";
		}
	} else {
		qDebug() << "Packet error:" << Packet::errorTypeToString(errorType);
	}
}
