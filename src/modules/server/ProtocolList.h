#pragma once

#include <QList>
#include <QSslSocket>
#include "Protocol.h"
#include "../lib/Version.h"

class ProtocolList : public QList<Protocol *> {

	public:
		ProtocolList(
			const Version &version = Version(0, 0, 0),
			const bool autoCleanup = true
		);
		~ProtocolList();

		void setVersion(const Version &version);
		Version getVersion() const;

		void setAutoCleanup(const bool autoCleanup);
		bool isAutoCleanup() const;

		Protocol *createProtocol(QSslSocket *sslSocket);
		Protocol *getProtocol(const QSslSocket *sslSocket);
		void removeProtocol(const QSslSocket *sslSocket);

	protected:
		bool autoCleanup = true;
		Version version;

};
