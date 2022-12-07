#pragma once

#include "RitLibraryDatabaseObject.h"
#include "UserRitTypeDatabaseObjectList.h"

class UserRitLibraryDatabaseObject : public RitLibraryDatabaseObject {

	Q_OBJECT

	public:
		UserRitLibraryDatabaseObject(
			RuntimeInformationType &rit,
			QObject *parent = nullptr
		);

		UserRitTypeDatabaseObjectList *getAll();

};
