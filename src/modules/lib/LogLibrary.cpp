#include "LogLibrary.h"
#include <QDateTime>

LogLibrary::LogLibrary(QObject *parent) : QObject(parent) {
}

LogLibrary::~LogLibrary() {
}

QString LogLibrary::createLogString(
	const QString &message,
	const bool error,
	const qint64 pid
) {
	if(pid != 0)
		return QString("PID %1 - [%2] %3: %4").arg(pid).arg(error ? "-" : "+").arg(QDateTime::currentDateTime().toString()).arg(message);
	return QString("[%1] %2: %3").arg(error ? "-" : "+").arg(QDateTime::currentDateTime().toString()).arg(message);
}
