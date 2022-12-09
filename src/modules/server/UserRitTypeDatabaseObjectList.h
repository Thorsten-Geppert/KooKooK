#pragma once

#include <QList>
#include "UserRitTypeDatabaseObject.h"

class UserRitTypeDatabaseObjectList : public QList<UserRitTypeDatabaseObject *> {

	public:
		UserRitTypeDatabaseObjectList(const bool autoClean = true);
		virtual ~UserRitTypeDatabaseObjectList();
		bool contains(const QString &username) const;
		void setAutoClean(const bool autoClean);
		bool isAutoClean() const;
	
	protected:
		bool autoClean = true;

};
