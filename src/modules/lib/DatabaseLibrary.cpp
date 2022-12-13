#include "DatabaseLibrary.h"
#include <QSqlQuery>

DatabaseLibrary::DatabaseLibrary(
	QSqlDatabase &db
) : db(
	db
) {
}

QString DatabaseLibrary::getPasswordByUsername(
	const QString &username,
	bool *exists
) const {
	QString password;

	QSqlQuery query(db);
	query.prepare("SELECT password FROM users WHERE username = :username");
	query.bindValue(":username", username);
	const bool userExists = query.exec() && query.next();
	if(userExists)
		password = query.value("password").toString();
	
	if(exists)
		*exists = userExists;

	return password;
}
