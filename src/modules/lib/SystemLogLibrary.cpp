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
	const bool error
) {
	syslog(error ? LOG_ERR : LOG_INFO, "%s", message.toLatin1().data());

	return true;
}
