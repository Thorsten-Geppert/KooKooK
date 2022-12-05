#pragma once

#include <QList>
#include "UserRitTypeDatabaseObject.h"

class UserRitTypeDatabaseObjectList : public QList<UserRitTypeDatabaseObject *> {

	public:
		UserRitTypeDatabaseObjectList();
		virtual ~UserRitTypeDatabaseObjectList();

};
