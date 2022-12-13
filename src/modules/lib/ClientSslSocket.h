#pragma once

#include "SslSocket.h"

class ClientSslSocket : public SslSocket {
	
	Q_OBJECT

	public:
		ClientSslSocket(
			QObject *parent = nullptr
		);

		ClientSslSocket(
			const Version &version,
			QObject *parent = nullptr
		);

		static bool parseAuthenticationString(
			const QString &authentication,
			Version &version,
			QUuid &uuid
		);

		bool parseAuthenticationString(
			const QString &authentication
		);

		bool answerWelcomeMessage(
			const QUuid &uuid,
			const QString &username,
			const QString &password
		);

};
