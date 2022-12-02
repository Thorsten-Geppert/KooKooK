#include "SystemLogLibrary.h"
#include <syslog.h>

SystemLogLibrary::SystemLogLibrary(
	QObject *parent
) : LogLibrary(
	parent
) {
}

bool SystemLogLibrary::log(
	const QString &message,
	const bool error,
	const qint64 pid
) {
	syslog(
		error ? LOG_ERR : LOG_INFO,
		"PID: %lld - %s",
		pid,
		message.toLatin1().data()
	);

	return true;
}
