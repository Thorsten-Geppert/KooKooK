#include "ServerSslSocket.h"
#include "DatabaseLibrary.h"

ServerSslSocket::ServerSslSocket(
	QSqlDatabase &db,
	QObject *parent
) : SslSocket(
	parent
), db(
	db
) {
	initialize();
}

ServerSslSocket::ServerSslSocket(
	QSqlDatabase &db,
	const Version &version,
	QObject *parent
) : SslSocket(
	parent
), db(
	db
) {
	initialize();
	setVersion(version);
}

bool ServerSslSocket::initialize() {
	if(!isInitialized()) {
		setUuid(QUuid::createUuid());

		setInitialized(true);

		return true;
	}

	return false;
}

void ServerSslSocket::setInitialized(const bool initialized) {
	this->initialized = initialized;
}

bool ServerSslSocket::isInitialized() const {
	return initialized;
}

QByteArray ServerSslSocket::generateWelcomeMessage(
	Version version,
	QUuid uuid
) {
	return QString("%1:%2").arg(version.toString(), uuid.toString()).toUtf8();
}

QByteArray ServerSslSocket::generateWelcomeMessage() const {
	return generateWelcomeMessage(getVersion(), getUuid());
}


bool ServerSslSocket::parseAuthenticationString(
	const QByteArray &message,
	QString &username,
	QByteArray &hash
) {
	const qsizetype at = message.indexOf("@");
	if(at >= 0) {
		username = message.sliced(0, at);
		hash = message.sliced(at + 1);
		return true;
	}

	return false;
}

bool ServerSslSocket::askWelcomeMessage() {
	return sendPacket("Authenticate", "Text", generateWelcomeMessage());
}

ServerSslSocket::LoginErrorType ServerSslSocket::endWelcomeMessage(
	const QByteArray &message,
	bool &sent,
	QString *username
) {
	LoginErrorType errorType = LoginErrorType::UNKNOWN;
	sent = false;

	if(message.isEmpty()) {
		errorType = LoginErrorType::EMPTY;
	} else {
		QString clientUsername;
		QByteArray clientHash;

		if(parseAuthenticationString(message, clientUsername, clientHash)) {
			if(username)
				*username = clientUsername;

			if(clientUsername.isEmpty()) {
				errorType = LoginErrorType::EMPTY_USER;
			} else if(clientHash.isEmpty()) {
				errorType = LoginErrorType::EMPTY_HASH;
			} else {
				bool userExists = false;
				DatabaseLibrary databaseLibrary(getDb());
				errorType = hash(
					clientUsername,
					databaseLibrary.getPasswordByUsername(clientUsername, &userExists)
				) == clientHash ? LoginErrorType::LOGGED_IN : LoginErrorType::NOT_LOGGED_IN;

				if(!userExists)
					errorType = LoginErrorType::NO_USER;
			}
		} else {
			errorType = LoginErrorType::PARSE;
		}
	}

	sent = sendPacket(
		"Authenticated",
		"Text",
		QString(errorType == LoginErrorType::LOGGED_IN ? "OK" : "NK")
	);

	return errorType;
}

QSqlDatabase &ServerSslSocket::getDb() {
	return db;
}
