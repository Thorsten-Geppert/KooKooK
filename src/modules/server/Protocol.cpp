#include "Protocol.h"
#include <QStringList>
#include <QCryptographicHash>

Protocol::Protocol(
	const Version &version,
	QUuid *generatedUuid
) {
	setVersion(version);
	generateAndSetUuid();
	if(generatedUuid)
		*generatedUuid = getUuid();
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
