#include "SslConfigurationType.h"
#include <QFile>
#include <QIODevice>
#include <QSsl>

SslConfigurationType::SslConfigurationType(
) : ConfigurationType(
) {
}

SslConfigurationType::SslConfigurationType(
	const QString &serverCaFilename,
	const QString &clientCaFilename,
	const QString &keyFilename,
	const QString &certificateFilename
) : ConfigurationType(
) {
	setServerCaFilename(serverCaFilename);
	setClientCaFilename(clientCaFilename);
	setKeyFilename(keyFilename);
	setCertificateFilename(certificateFilename);
}

void SslConfigurationType::setServerCaFilename(const QString &serverCaFilename) {
	this->serverCaFilename = serverCaFilename;
}

QString SslConfigurationType::getServerCaFilename() const {
	return serverCaFilename;
}

void SslConfigurationType::setClientCaFilename(const QString &clientCaFilename) {
	this->clientCaFilename = clientCaFilename;
}

QString SslConfigurationType::getClientCaFilename() const {
	return clientCaFilename;
}

void SslConfigurationType::setKeyFilename(const QString &keyFilename) {
	this->keyFilename = keyFilename;
}

QString SslConfigurationType::getKeyFilename() const {
	return keyFilename;
}

QSslKey SslConfigurationType::getKey(bool &ok) const {
	QSslKey sslKey;

	ok = false;
	QFile keyFile(getKeyFilename());
	if(keyFile.open(QIODevice::ReadOnly)) {
		sslKey = QSslKey(keyFile.readAll(), QSsl::Rsa);

		keyFile.close();

		ok = true;
	}

	return sslKey;
}

void SslConfigurationType::setCertificateFilename(const QString &certificateFilename) {
	this->certificateFilename = certificateFilename;
}

QString SslConfigurationType::getCertificateFilename() const {
	return certificateFilename;
}

QSslCertificate SslConfigurationType::getCertificate(bool &ok) const {
	return loadCertificate(getCertificateFilename(), &ok);
}

QString SslConfigurationType::toString() const {
	return QString(
		"SCA: %1, CCA %2, Key %3, Certificate: %4"
	).arg(
		getServerCaFilename()
	).arg(
		getClientCaFilename()
	).arg(
		getKeyFilename()
	).arg(
		getCertificateFilename()
	);
}

bool SslConfigurationType::cache(LogLibrary *logLibrary) {
	Cache.setServerCaFilename(getServerCaFilename());
	Cache.setClientCaFilename(getClientCaFilename());
	Cache.setVerify(getVerifyMode());
	
	bool ok = false;
	QSslKey key = getKey(ok);
	if(!ok) {
		if(logLibrary)
			logLibrary->log(QString("Could not load ssl key %1").arg(getKeyFilename()));
	} else {
		Cache.setKey(key);
	}

	QSslCertificate certificate = getCertificate(ok);
	if(!ok) {
		if(logLibrary)
			logLibrary->log(QString("Could not load ssl certificate %1").arg(getCertificateFilename()));
	} else {
		Cache.setCertificate(certificate);
	}

	return ok;
}

QSslCertificate SslConfigurationType::loadCertificate(const QString &certificateFilename, bool *ok) {
	QSslCertificate sslCertificate;

	bool tmpOk = false;
	QFile certificateFile(certificateFilename);
	if(certificateFile.open(QIODevice::ReadOnly)) {
		sslCertificate = QSslCertificate(certificateFile.readAll());

		certificateFile.close();

		tmpOk = true;
	}

	if(ok)
		*ok = tmpOk;

	return sslCertificate;
}

void SslConfigurationType::setVerify(const bool verify) {
	this->verify = verify;
}

bool SslConfigurationType::getVerify() const {
	return verify;
}

QSslSocket::PeerVerifyMode SslConfigurationType::getVerifyMode() const {
	return getVerify() ? QSslSocket::VerifyPeer : QSslSocket::VerifyNone;
}
