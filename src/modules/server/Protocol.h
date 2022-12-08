#pragma once

#include "../lib/Version.h"
#include <QSslSocket>
#include <QUuid>

class Protocol {

	public:
		Protocol(
			const Version &version,
			QUuid *generatedUuid = nullptr
		);

		void setVersion(const Version &version);
		Version getVersion() const;
		QString getVersionString() const;

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

	private:
		Version version;
		QUuid uuid;

};
