#pragma once

#include "RitTypeDatabaseObject.h"

class UserRitTypeDatabaseObject : public RitTypeDatabaseObject {

	public:
		UserRitTypeDatabaseObject(
			RuntimeInformationType &rit,
			QObject *parent = nullptr
		);

		UserRitTypeDatabaseObject(
			RuntimeInformationType &rit,
			const QString &username,
			const QString &password,
			QObject *parent = nullptr
		);

		void setUsername(const QString &username);
		QString getUsername() const;

		void setPassword(const QString &password);
		QString getPassword();
	
	protected:
		QString username;
		QString password; // hashed

};
