#pragma once

#include <QObject>
#include <QSqlDatabase>

class DatabaseObject : public QObject {

	Q_OBJECT

	public:
		DatabaseObject(
			QSqlDatabase &db,
			const QString &className = "DatabaseObject",
			QObject *parent = nullptr
		);

		virtual ~DatabaseObject();

		virtual QSqlDatabase &getDb();

		virtual void setClassName(const QString &className);
		virtual QString getClassName() const;
	
	protected:
		QSqlDatabase &db;
		QString className;

};
