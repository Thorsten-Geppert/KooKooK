#pragma once

#include "ConfigurationType.h"
#include <QString>
#include <QSslCertificate>
#include <QSslKey>

class SslConfigurationType : public ConfigurationType {

	public:
		SslConfigurationType();
		SslConfigurationType(
			const QString &serverCaFilename,
			const QString &clientCaFilename,
			const QString &keyFilename,
			const QString &certificateFilename
		);

		void setServerCaFilename(const QString &serverCaFilename);
		QString getServerCaFilename() const;

		void setClientCaFilename(const QString &clientCaFilename);
		QString getClientCaFilename() const;

		void setKeyFilename(const QString &keyFilename);
		QString getKeyFilename() const;
		QSslKey getKey(bool *ok = nullptr) const;

		void setCertificateFilename(const QString &certificateFilename);
		QString getCertificateFilename() const;
		QSslCertificate getCertificate(bool *ok = nullptr) const;

		QString toString() const;

	protected:
		QString serverCaFilename;
		QString clientCaFilename;
		QString keyFilename;
		QString certificateFilename;

};
