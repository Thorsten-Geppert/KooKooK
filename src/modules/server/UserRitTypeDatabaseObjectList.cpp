#include "UserRitTypeDatabaseObjectList.h"

UserRitTypeDatabaseObjectList::UserRitTypeDatabaseObjectList(
	const bool autoClean
) : QList<UserRitTypeDatabaseObject *>(
) {
	setAutoClean(autoClean);
}

UserRitTypeDatabaseObjectList::~UserRitTypeDatabaseObjectList() {
	if(isAutoClean())
		qDeleteAll(*this);
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

void UserRitTypeDatabaseObjectList::setAutoClean(const bool autoClean) {
	this->autoClean = autoClean;
}

bool UserRitTypeDatabaseObjectList::isAutoClean() const {
	return autoClean;
}
