#include "UserRitLibraryDatabaseObject.h"
#include <QSqlQuery>

UserRitLibraryDatabaseObject::UserRitLibraryDatabaseObject(
	RuntimeInformationType &rit,
	QObject *parent
) : RitLibraryDatabaseObject(
	rit,
	"UserRitLibraryDatabaseObject",
	parent
) {
}

UserRitTypeDatabaseObjectList *UserRitLibraryDatabaseObject::getAll() {
	UserRitTypeDatabaseObjectList *users = new UserRitTypeDatabaseObjectList;

	QSqlQuery query(getDb());
	if(query.exec("SELECT * FROM users WHERE active = 1 ORDER BY username")) {
		while(query.next()) {
			users->append(new UserRitTypeDatabaseObject(
				rit,
				query.value("username").toString(),
				query.value("password").toString()
			));
		}
		query.finish();
	}

	return users;
}
