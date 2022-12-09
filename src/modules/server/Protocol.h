#pragma once

#include "../lib/Version.h"
#include "../lib/Packet.h"
#include "RuntimeInformationType.h"
#include <QSslSocket>
#include <QUuid>

class Protocol {

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


		Protocol(
			const Version &version,
			QSslSocket &sslSocket,
			QUuid *generatedUuid = nullptr
		);

		void setVersion(const Version &version);
		Version getVersion() const;
		QString getVersionString() const;

		QSslSocket &getSslSocket();

		static bool parseAuthenticationString(
			const QString &authentication,
			Version &version,
			QUuid &uuid
		);

		bool parseAuthenticationString(
			const QString &authentication
		);

		static QByteArray hash(
			const QString &username,
			const QString &password,
			const QUuid &uuid
		);

		QByteArray hash(
			const QString &username,
			const QString &password
		);

		void setUuid(const QUuid &uuid);
		QUuid getUuid() const;
		QUuid generateAndSetUuid();
		static QUuid generateUuid();

		static QByteArray generateWelcomeMessage(
			Version version,
			QUuid uuid
		);
		QByteArray generateWelcomeMessage() const;

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
			QSslSocket &sslSocket,
			const Packet &packet
		);

		static bool sendPacket(
			QSslSocket &sslSocket,
			const QString &command,
			const QString &format,
			const QByteArray &data
		);

		static bool sendPacket(
			QSslSocket &sslSocket,
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

		bool askWelcomeMessage();
		bool answerWelcomeMessage(
			const QUuid &uuid,
			const QString &username,
			const QString &password
		);
		LoginErrorType endWelcomeMessage(
			RuntimeInformationType::UserCacheType &userCache,
			const QByteArray &message,
			bool &sent,
			QString *username = nullptr
		);

		static bool parseAuthenticationString(
			const QByteArray &message,
			QString &username,
			QByteArray &hash
		);

		static QString loginErrorTypeToString(const LoginErrorType &errorType);

	private:
		Version version;
		QUuid uuid;
		QSslSocket &sslSocket;

};
