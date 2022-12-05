#pragma once

#include "DatabaseObject.h"

class TypeDatabaseObject : public DatabaseObject {
	
	Q_OBJECT

	public:
		TypeDatabaseObject(
			QSqlDatabase &db,
			const QString &className = "TypeDatabaseObject",
			QObject *parent = nullptr
		);

};
