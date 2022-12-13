#pragma once

#include <QSqlDatabase>

class DatabaseLibrary {

	public:
		DatabaseLibrary(QSqlDatabase &db);

		QString getPasswordByUsername(
			const QString &username,
			bool *exists
		) const;
	
	protected:
		QSqlDatabase &db;

};
