#pragma once

#include "ConfigurationType.h"
#include <QString>
#include <QSslCertificate>
#include <QSslSocket>
#include <QSslKey>
#include "../../lib/LogLibrary.h"

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
		QSslKey getKey(bool &ok) const;

		void setCertificateFilename(const QString &certificateFilename);
		QString getCertificateFilename() const;
		QSslCertificate getCertificate(bool &ok) const;

		static QSslCertificate loadCertificate(const QString &certificateFilename, bool *ok = nullptr);

		QString toString() const;

		struct CacheStruct {
			private:
				QString serverCaFilename;
				QString clientCaFilename;
				QSslKey key;
				QSslCertificate certificate;
				QSslSocket::PeerVerifyMode verify;
				
			public:
				QString getServerCaFilename() const { return serverCaFilename; }
				QString getClientCaFilename() const { return clientCaFilename; }
				QSslKey getKey() const { return key; }
				QSslCertificate getCertificate() const { return certificate; };
				QSslSocket::PeerVerifyMode getVerify() const { return verify; };

				void setServerCaFilename(const QString &serverCaFilename) { this->serverCaFilename = serverCaFilename; }
				void setClientCaFilename(const QString &clientCaFilename) { this->clientCaFilename = clientCaFilename; }
				void setKey(const QSslKey &key) { this->key = key; }
				void setCertificate(const QSslCertificate &certificate) { this->certificate = certificate; }
				void setVerify(const QSslSocket::PeerVerifyMode verify) { this->verify = verify; };

		} Cache;

		bool cache(LogLibrary *logLibrary = nullptr);

		void setVerify(const bool verify);
		bool getVerify() const;
		QSslSocket::PeerVerifyMode getVerifyMode() const;

	protected:
		QString serverCaFilename;
		QString clientCaFilename;
		QString keyFilename;
		QString certificateFilename;
		bool verify = true;

};
