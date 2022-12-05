#pragma once

#include "lib/LibraryDatabaseObject.h"
#include "RuntimeInformationType.h"

class RitLibraryDatabaseObject : public LibraryDatabaseObject {

	Q_OBJECT

	public:
		RitLibraryDatabaseObject(
			RuntimeInformationType &rit,
			const QString &className = "RitLibraryDatabaseObject",
			QObject *parent = nullptr
		);

	protected:
		RuntimeInformationType &rit;

};
