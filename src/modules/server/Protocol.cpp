#include "Protocol.h"
#include <QStringList>
#include <QCryptographicHash>

Protocol::Protocol(
	const Version &version,
	QSslSocket *sslSocket,
	QUuid *generatedUuid
) : sslSocket(
	sslSocket
) {
	setVersion(version);
	generateAndSetUuid();
	if(generatedUuid)
		*generatedUuid = getUuid();
}

Protocol::~Protocol() {
	if(sslSocket)
		delete sslSocket;
}

void Protocol::setVersion(const Version &version) {
	this->version = version;
}

Version Protocol::getVersion() const {
	return version;
}

QString Protocol::getVersionString() const {
	return getVersion().toString();
}

QSslSocket *Protocol::getSslSocket() {
	return sslSocket;
}

bool Protocol::parseAuthenticationString(
	const QString &authentication,
	Version &version,
	QUuid &uuid
) {
	const QStringList list = authentication.split(":");
	if(list.count() == 2) {
		if(version.set(list[0])) {
			uuid = QUuid::fromString(list[1]);
			return !uuid.isNull();
		}
	}

	return false;
}

bool Protocol::parseAuthenticationString(
	const QString &authentication
) {
	return parseAuthenticationString(
		authentication,
		version,
		uuid
	);
}

QByteArray Protocol::hash(
	const QString &username,
	const QString &password,
	const QUuid &uuid
) {
	QByteArray passphrase;

	passphrase.append(username.toUtf8());
	passphrase.append(uuid.toString().toUtf8());
	passphrase.append(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Md5));

	return QCryptographicHash::hash(passphrase, QCryptographicHash::Keccak_512);
}

QByteArray Protocol::hash(
	const QString &username,
	const QString &password
) {
	return hash(username, password, getUuid());
}

void Protocol::setUuid(const QUuid &uuid) {
	this->uuid = uuid;
}

QUuid Protocol::getUuid() const {
	return uuid;
}

QUuid Protocol::generateAndSetUuid() {
	const QUuid uuid = generateUuid();
	setUuid(uuid);
	return uuid;
}

QUuid Protocol::generateUuid() {
	return QUuid::createUuid();
}

QByteArray Protocol::generateWelcomeMessage(
	Version version,
	QUuid uuid
) {
	return QString("%1:%2").arg(version.toString(), uuid.toString()).toUtf8();
}

QByteArray Protocol::generateWelcomeMessage() const {
	return generateWelcomeMessage(getVersion(), getUuid());
}

Packet Protocol::createPacket(
	const QString &command,
	const QString &format,
	const QByteArray &data
) {
	return Packet(command, format, data);
}

bool Protocol::sendPacket(
	QSslSocket *sslSocket,
	const Packet &packet
) {
	if(!sslSocket)
		return false;

	const QByteArray packetString = packet.toByteArray();
	return sslSocket->write(packetString) == packetString.size();
}

bool Protocol::sendPacket(
	QSslSocket *sslSocket,
	const QString &command,
	const QString &format,
	const QByteArray &data
) {
	return sendPacket(
		sslSocket,
		createPacket(
			command,
			format,
			data
		)
	);
}

bool Protocol::sendPacket(
	QSslSocket *sslSocket,
	const QString &command,
	const QString &format,
	const QString &data
) {
	return sendPacket(
		sslSocket,
		command,
		format,
		data.toUtf8()
	);
}

bool Protocol::sendPacket(const Packet &packet) {
	return sendPacket(getSslSocket(), packet);
}

bool Protocol::sendPacket(
	const QString &command,
	const QString &format,
	const QByteArray &data
) {
	return sendPacket(getSslSocket(), command, format, data);
}

bool Protocol::sendPacket(
	const QString &command,
	const QString &format,
	const QString &data
) {
	return sendPacket(getSslSocket(), command, format, data);
}

bool Protocol::askWelcomeMessage() {
	return sendPacket("Authenticate", "Text", generateWelcomeMessage());
}

bool Protocol::answerWelcomeMessage(
	const QUuid &uuid,
	const QString &username,
	const QString &password
) {
	QByteArray answer = username.toUtf8();
	answer.append("@");
	answer.append(hash(username, password, uuid));
	return sendPacket(
		"Authenticate",
		"Text",
		answer
	);
}

Packet Protocol::createPacket(
	const QByteArray &packet,
	Packet::ErrorType *errorType
) {
	return Packet::parse(
		packet,
		Packet::getDefaultDelimiter(),
		errorType
	);
}

bool Protocol::parseAuthenticationString(
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

Protocol::LoginErrorType Protocol::endWelcomeMessage(
	RuntimeInformationType::UserCacheType &userCache,
	const QByteArray &message,
	bool &sent,
	QString *username
) {
	LoginErrorType errorType = LoginErrorType::UNKNOWN;

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
				if(userCache.localData().contains(clientUsername)) {
					if(hash(
						clientUsername,
						userCache.localData().value(clientUsername)
					) == clientHash) {
						errorType = LoginErrorType::LOGGED_IN;
					} else {
						errorType = LoginErrorType::NOT_LOGGED_IN;
					}
				} else {
					errorType = LoginErrorType::NO_USER;
				}
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

QString Protocol::loginErrorTypeToString(const LoginErrorType &errorType) {
	QString message;

	switch(errorType) {
		case LoginErrorType::LOGGED_IN: message = "LOGGED_IN: Login successfull"; break;
		case LoginErrorType::UNKNOWN: message = "UNKNOWN: Unknown error occured"; break;
		case LoginErrorType::EMPTY: message = "EMPTY: Packet data is empty"; break;
		case LoginErrorType::PARSE: message = "PARSE: Unaible to parse packet data"; break;
		case LoginErrorType::EMPTY_USER: message = "EMPTY_USER: Empty user was given"; break;
		case LoginErrorType::NO_USER: message = "NO_USER: No such user in database"; break;
		case LoginErrorType::EMPTY_HASH: message = "EMPTY_HASH: Empty hash was given"; break;
		case LoginErrorType::NOT_LOGGED_IN: message = "NOT_LOGGED_IN: Could not login"; break;
	}

	return message;
}
