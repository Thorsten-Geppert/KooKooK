#pragma once

#include <QList>
#include <QSqlDatabase>
#include "ServerSslSocket.h"
#include "Version.h"

class ServerSslSocketList : public QList<ServerSslSocket *> {

	public:
		ServerSslSocketList(
			QSqlDatabase &db,
			const Version &version,
			QObject *parent = nullptr,
			const bool autoCleanup = true
		);

		virtual ~ServerSslSocketList();

		void setParent(QObject *parent);
		QObject *getParent();

		void setAutoCleanup(const bool autoCleanup);
		bool isAutoCleanup() const;

		void setVersion(const Version &version);
		Version getVersion() const;

		ServerSslSocket *add();
		ServerSslSocket *cast(QObject *serverSslSocket);

		QSqlDatabase &getDb();
	
	protected:
		QObject *parent = nullptr;
		bool autoCleanup = true;
		Version version;
		QSqlDatabase &db;

};
