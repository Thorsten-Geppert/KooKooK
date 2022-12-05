#include "UserRitTypeDatabaseObjectList.h"

UserRitTypeDatabaseObjectList::UserRitTypeDatabaseObjectList(
) : QList<UserRitTypeDatabaseObject *>(
) {
}

UserRitTypeDatabaseObjectList::~UserRitTypeDatabaseObjectList() {
	qDeleteAll(*this);
}
