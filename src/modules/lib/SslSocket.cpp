#include "SslSocket.h"
#include "DatabaseLibrary.h"

SslSocket::SslSocket(
	QObject *parent
) : QSslSocket(
	parent
) {
}

SslSocket::SslSocket(
	const Version &version,
	QObject *parent
) : QSslSocket(
	parent
) {
	setVersion(version);
}

void SslSocket::setVersion(const Version &version) {
	this->version = version;
}

Version SslSocket::getVersion() const {
	return version;
}

QByteArray SslSocket::hash(
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

QByteArray SslSocket::hash(
	const QString &username,
	const QString &password
) {
	return hash(username, password, getUuid());
}

void SslSocket::setUuid(const QUuid &uuid) {
	this->uuid = uuid;
}

QUuid SslSocket::getUuid() const {
	return uuid;
}

QUuid SslSocket::generateAndSetUuid() {
	const QUuid uuid = generateUuid();
	setUuid(uuid);
	return uuid;
}

QUuid SslSocket::generateUuid() {
	return QUuid::createUuid();
}

Packet SslSocket::createPacket(
	const QString &command,
	const QString &format,
	const QByteArray &data
) {
	return Packet(command, format, data);
}

bool SslSocket::sendPacket(
	QSslSocket *sslSocket,
	const Packet &packet
) {
	if(!sslSocket)
		return false;

	const QByteArray packetString = packet.toByteArray();
	return sslSocket->write(packetString) == packetString.size();
}

bool SslSocket::sendPacket(
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

bool SslSocket::sendPacket(
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

bool SslSocket::sendPacket(const Packet &packet) {
	return sendPacket(this, packet);
}

bool SslSocket::sendPacket(
	const QString &command,
	const QString &format,
	const QByteArray &data
) {
	return sendPacket(this, command, format, data);
}

bool SslSocket::sendPacket(
	const QString &command,
	const QString &format,
	const QString &data
) {
	return sendPacket(this, command, format, data);
}

Packet SslSocket::createPacket(
	const QByteArray &packet,
	Packet::ErrorType *errorType
) {
	return Packet::parse(
		packet,
		Packet::getDefaultDelimiter(),
		errorType
	);
}

QString SslSocket::loginErrorTypeToString(const LoginErrorType &errorType) {
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
