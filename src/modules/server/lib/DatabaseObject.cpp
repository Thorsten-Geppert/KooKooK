#include "DatabaseObject.h"

DatabaseObject::DatabaseObject(
	QSqlDatabase &db,
	const QString &className,
	QObject *parent
) : QObject(
	parent
), db(
	db
) {
	setClassName(className);
}

DatabaseObject::~DatabaseObject() {
}

void DatabaseObject::setClassName(const QString &className) {
	this->className = className;
}

QString DatabaseObject::getClassName() const {
	return className;
}

QSqlDatabase &DatabaseObject::getDb() {
	return db;
}
