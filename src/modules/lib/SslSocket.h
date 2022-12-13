#pragma once

#include <QSslSocket>
#include <QUuid>
#include "Version.h"
#include "Packet.h"

class SslSocket : public QSslSocket {
	
	Q_OBJECT

	public:
		typedef enum class LoginErrorEnumration : unsigned int {
			LOGGED_IN = 0,
			UNKNOWN,
			EMPTY,
			PARSE,
			EMPTY_USER,
			NO_USER,
			EMPTY_HASH,
			NOT_LOGGED_IN
		} LoginErrorType;

		SslSocket(
			QObject *parent = nullptr
		);
		SslSocket(
			const Version &version,
			QObject *parent = nullptr
		);

		void setVersion(const Version &version);
		Version getVersion() const;

		QUuid getUuid() const;

		static QByteArray hash(
			const QString &username,
			const QString &password,
			const QUuid &uuid
		);

		QByteArray hash(
			const QString &username,
			const QString &password
		);

		QUuid generateAndSetUuid();
		static QUuid generateUuid();

		static Packet createPacket(
			const QString &command,
			const QString &format,
			const QByteArray &data
		);
		static Packet createPacket(
			const QByteArray &packet,
			Packet::ErrorType *errorTyp = nullptr
		);

		static bool sendPacket(
			QSslSocket *sslSocket,
			const Packet &packet
		);

		static bool sendPacket(
			QSslSocket *sslSocket,
			const QString &command,
			const QString &format,
			const QByteArray &data
		);

		static bool sendPacket(
			QSslSocket *sslSocket,
			const QString &command,
			const QString &format,
			const QString &data
		);

		bool sendPacket(const Packet &packet);
		bool sendPacket(
			const QString &command,
			const QString &format,
			const QByteArray &data
		);
		bool sendPacket(
			const QString &command,
			const QString &format,
			const QString &data
		);

		static QString loginErrorTypeToString(const LoginErrorType &errorType);

	protected:
		Version version;
		QUuid uuid;

		void setUuid(const QUuid &uuid);

};
