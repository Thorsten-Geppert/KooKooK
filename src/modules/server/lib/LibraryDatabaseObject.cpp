#include "LibraryDatabaseObject.h"

LibraryDatabaseObject::LibraryDatabaseObject(
	QSqlDatabase &db,
	const QString &className,
	QObject *parent
) : DatabaseObject(
	db,
	className,
	parent
) {
}
