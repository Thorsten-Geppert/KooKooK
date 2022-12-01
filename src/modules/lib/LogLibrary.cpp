#include "LogLibrary.h"
#include <QDateTime>

LogLibrary::LogLibrary(QObject *parent) : QObject(parent) {
}

LogLibrary::~LogLibrary() {
}

QString LogLibrary::createLogString(
	const QString &message,
	const bool error
) {
	return QString("%1 %2: %3").arg(error ? "-" : "+").arg(QDateTime::currentDateTime().toString()).arg(message);
}
