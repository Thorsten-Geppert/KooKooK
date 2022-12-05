#include "TypeDatabaseObject.h"

TypeDatabaseObject::TypeDatabaseObject(
	QSqlDatabase &db,
	const QString &className,
	QObject *parent
) : DatabaseObject(
	db,
	className,
	parent
) {
}
