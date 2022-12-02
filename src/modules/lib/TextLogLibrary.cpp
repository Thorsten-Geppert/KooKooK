#include "TextLogLibrary.h"
#include <QFile>
#include <QTextStream>
#include "SystemLogLibrary.h"

TextLogLibrary::TextLogLibrary(
	const QString &logFilename,
	const bool fallbackToSyslog,
	QObject *parent
) : LogLibrary(
	parent
) {
	setLogFilename(logFilename);
	setFallbackToSyslog(fallbackToSyslog);
}

bool TextLogLibrary::log(
	const QString &message,
	const bool error,
	const qint64 pid
) {
	QFile file(getLogFilename());
	if(file.open(QIODevice::WriteOnly | QIODevice::Append)) {
		QTextStream stream(&file);
		stream << createLogString(message, error, pid) << Qt::endl;
		file.close();

		return true;
	}

	if(getFallbackToSyslog()) {
		SystemLogLibrary systemLogLibrary(parent());
		log(message, error);
	}

	return false;
}

void TextLogLibrary::setLogFilename(const QString &logFilename) {
	this->logFilename = logFilename;
}

QString TextLogLibrary::getLogFilename() const {
	return logFilename;
}

void TextLogLibrary::setFallbackToSyslog(const bool fallbackToSyslog) {
	this->fallbackToSyslog = fallbackToSyslog;
}

bool TextLogLibrary::getFallbackToSyslog() const {
	return fallbackToSyslog;
}
