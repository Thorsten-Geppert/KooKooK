#include "RitLibraryDatabaseObject.h"

RitLibraryDatabaseObject::RitLibraryDatabaseObject(
	RuntimeInformationType &rit,
	const QString &className,
	QObject *parent
) : LibraryDatabaseObject(
	rit.getDb(),
	className,
	parent
), rit(
	rit
) {
}
