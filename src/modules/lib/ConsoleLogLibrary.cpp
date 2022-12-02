#include "ConsoleLogLibrary.h"
#include <QtGlobal>
#include <QDebug>

ConsoleLogLibrary::ConsoleLogLibrary(
	QObject *parent
) : LogLibrary(
	parent
) {
}

bool ConsoleLogLibrary::log(
	const QString &message,
	const bool error,
	const qint64 pid
) {
	if(error)
		qCritical("%s", createLogString(message, error, pid).toLatin1().data());
	else
		qDebug("%s", createLogString(message, error, pid).toLatin1().data());

	return true;
}
