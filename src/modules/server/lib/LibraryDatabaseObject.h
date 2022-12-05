#pragma once

#include "DatabaseObject.h"

class LibraryDatabaseObject : public DatabaseObject {
	
	Q_OBJECT

	public:
		LibraryDatabaseObject(
			QSqlDatabase &db,
			const QString &className = "LibraryDatabaseObject",
			QObject *parent = nullptr
		);

};
