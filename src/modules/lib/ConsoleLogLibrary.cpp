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
	const bool error
) {
	if(error)
		qCritical("%s", createLogString(message, error).toLatin1().data());
	else
		qDebug("%s", createLogString(message, error).toLatin1().data());

	return true;
}
