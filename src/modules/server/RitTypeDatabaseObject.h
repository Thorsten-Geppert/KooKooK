#pragma once

#include "lib/TypeDatabaseObject.h"
#include "RuntimeInformationType.h"

class RitTypeDatabaseObject : public TypeDatabaseObject {

	Q_OBJECT

	public:
		RitTypeDatabaseObject(
			RuntimeInformationType &rit,
			const QString &className = "RitTypeDatabaseObject",
			QObject *parent = nullptr
		);

	protected:
		RuntimeInformationType &rit;

};
