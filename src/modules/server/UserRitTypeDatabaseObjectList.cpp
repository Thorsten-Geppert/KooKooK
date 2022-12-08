#include "UserRitTypeDatabaseObjectList.h"

UserRitTypeDatabaseObjectList::UserRitTypeDatabaseObjectList(
) : QList<UserRitTypeDatabaseObject *>(
) {
}

UserRitTypeDatabaseObjectList::~UserRitTypeDatabaseObjectList() {
	qDeleteAll(*this);
	qDebug() << "called";
}

bool UserRitTypeDatabaseObjectList::contains(const QString &username) const {
	UserRitTypeDatabaseObject *user = nullptr;

	const int counter = count();
	for(int i = 0; i < counter; i++) {
		user = value(i);
		if(user && user->getUsername() == username)
			return true;
	}

	return false;
}
