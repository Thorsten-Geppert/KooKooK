#pragma once

#include <QList>
#include "ServerThread.h"

class ServerThreadList : public QList<ServerThread *> {

	public:
		ServerThreadList();

};
