#pragma once

#include "SslSocket.h"
#include <QSqlDatabase>

class ServerSslSocket : public SslSocket {
	
	Q_OBJECT

	public:
		ServerSslSocket(
			QSqlDatabase &db,
			QObject *parent = nullptr
		);
		ServerSslSocket(
			QSqlDatabase &db,
			const Version &version,
			QObject *parent = nullptr
		);

		bool isInitialized() const;

		static QByteArray generateWelcomeMessage(
			Version version,
			QUuid uuid
		);
		QByteArray generateWelcomeMessage() const;

		bool askWelcomeMessage();
		LoginErrorType endWelcomeMessage(
			const QByteArray &message,
			bool &sent,
			QString *username = nullptr
		);

		static bool parseAuthenticationString(
			const QByteArray &message,
			QString &username,
			QByteArray &hash
		);

		QSqlDatabase &getDb();
	
	protected:
		Version version;
		QUuid uuid;
		bool initialized = false;
		QSqlDatabase &db;

		bool initialize();
		void setInitialized(const bool initialized);

};
