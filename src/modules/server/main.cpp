#include <QCoreApplication>
#include <QDebug>
#include "Server.h"

int main(int argc, char *argv[]) {
	QCoreApplication app(argc, argv);

	Server server;
	if(!server.start()) {
		qDebug() << "Could not start server";
	}

	return app.exec();
}
