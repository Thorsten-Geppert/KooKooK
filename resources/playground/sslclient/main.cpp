#include <QCoreApplication>
#include "Client.h"

int main(int argc, char *argv[]) {
	QCoreApplication app(argc, argv);

	int count = 1;
	if(argc == 2)
		count = atoi(argv[1]);

	Client client;
	if(client.connectToServer(count))
		return app.exec();
	
	return 1;
}
