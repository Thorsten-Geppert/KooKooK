#include "RitTypeDatabaseObject.h"

RitTypeDatabaseObject::RitTypeDatabaseObject(
	RuntimeInformationType &rit,
	const QString &className,
	QObject *parent
) : TypeDatabaseObject(
	rit.getDb(),
	className,
	parent
), rit(
	rit
) {
}

