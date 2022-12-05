#include "UserRitTypeDatabaseObject.h"

UserRitTypeDatabaseObject::UserRitTypeDatabaseObject(
	RuntimeInformationType &rit,
	QObject *parent
) : RitTypeDatabaseObject(
	rit,
	"UserRitTypeDatabaseObject",
	parent
) {
}

UserRitTypeDatabaseObject::UserRitTypeDatabaseObject(
	RuntimeInformationType &rit,
	const QString &username,
	const QString &password,
	QObject *parent
) : RitTypeDatabaseObject(
	rit,
	"UserRitTypeDatabaseObject",
	parent
) {
	setUsername(username);
	setPassword(password);
}

void UserRitTypeDatabaseObject::setUsername(const QString &username) {
	this->username = username;
}

QString UserRitTypeDatabaseObject::getUsername() const {
	return username;
}

void UserRitTypeDatabaseObject::setPassword(const QString &password) {
	this->password = password;
}

QString UserRitTypeDatabaseObject::getPassword() {
	return password;
}
