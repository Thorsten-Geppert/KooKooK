#include <QCoreApplication>
#include <QObject>
#include <QDebug>
#include "Server.h"
#include "RuntimeInformationType.h"
#include "Configuration.h"

int main(int argc, char *argv[]) {
	QCoreApplication app(argc, argv);

	RuntimeInformationType rit(CONFIGURATION_FILENAME);

	Server server;
	QObject::connect(
		&server,
		&Server::exit,
		&app,
		&QCoreApplication::exit
	);
	if(!server.start()) {
		qDebug() << "Could not start server";
	}

	return app.exec();
}
