#include <QCoreApplication>
#include <QObject>
#include <QDebug>
#include <iostream>
#include "Server.h"
#include "RuntimeInformationType.h"

void usage(const char *program) {
	std::cout
		<< "Usage: "
		<< program
		<< " <configuraiton.ini>"
		<< std::endl
	;
}

int main(int argc, char *argv[]) {
	if(argc != 2) {
		usage(argv[0]);
		return 1;
	}

	RuntimeInformationType rit;
	if(rit.loadConfiguration(argv[1])) {
		QCoreApplication app(argc, argv);

		Server server(rit);
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

	return 2;
}
