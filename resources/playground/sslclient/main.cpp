#include <QCoreApplication>
#include "Client.h"

int main(int argc, char *argv[]) {
	QCoreApplication app(argc, argv);

	Client client;
	if(client.connectToServer())
		return app.exec();
	
	return 1;
}
