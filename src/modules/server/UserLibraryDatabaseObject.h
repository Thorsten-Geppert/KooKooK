#pragma once

#include "lib/LibraryDatabaseObject.h"
#include "RuntimeInformationType.h"

class UserLibraryDatabaseObject : public LibraryDatabaseObject {

	public:
		UserLibraryDatabaseObject(
			RuntimeInformationType &rit
		);

};
