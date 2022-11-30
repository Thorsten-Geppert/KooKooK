#pragma once

#include <QObject>
#include <QMutex>
#include "ServerThreadList.h"

class ServerThreadManager : public QObject {

	Q_OBJECT

	public:
		ServerThreadManager(QObject *parent = nullptr);
		bool create(const qintptr clientSocketDescriptor);

		int getCount() const;

		bool stop(
			unsigned int *quittedThreadCount = nullptr,
			unsigned int *terminatedThreadCount = nullptr
		);

	private:
		ServerThreadList serverThreadList;
		QMutex serverThreadMutex;

};
