#include "ClientSslSocket.h"

ClientSslSocket::ClientSslSocket(
	QObject *parent
) : SslSocket(
	parent
) {
}

ClientSslSocket::ClientSslSocket(
	const Version &version,
	QObject *parent
) : SslSocket(
	parent
) {
	setVersion(version);
}

bool ClientSslSocket::parseAuthenticationString(
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

bool ClientSslSocket::parseAuthenticationString(
	const QString &authentication
) {
	return parseAuthenticationString(
		authentication,
		version,
		uuid
	);
}

bool ClientSslSocket::answerWelcomeMessage(
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
