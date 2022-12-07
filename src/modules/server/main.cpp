#include <QCoreApplication>
#include <QObject>
#include <QDebug>
#include <iostream>
#include <signal.h>
#include "Server.h"
#include "RuntimeInformationType.h"

static void usage(const char *program) {
	std::cout
		<< "Usage: "
		<< program
		<< " <configuration.ini>"
		<< std::endl
	;
}

enum class SetupUnixSignalHandlersEnumeration : short {
	NONE,
	HUP,
	TERM,
	BOTH
};

static SetupUnixSignalHandlersEnumeration setupUnixSignalHandlers() {
	struct sigaction hup, term;

	hup.sa_handler = Server::hupSignalHandler;
	sigemptyset(&hup.sa_mask);
	hup.sa_flags = 0;
	hup.sa_flags |= SA_RESTART;

	const int hupResult = sigaction(SIGHUP, &hup, 0);
	
	term.sa_handler = Server::termSignalHandler;
	sigemptyset(&term.sa_mask);
	term.sa_flags = 0;
	term.sa_flags |= SA_RESTART;

	const int termResult = sigaction(SIGTERM, &term, 0);
	
	if(hupResult != 0 && termResult != 0)
		return SetupUnixSignalHandlersEnumeration::BOTH;
	else if(hupResult != 0)
		return SetupUnixSignalHandlersEnumeration::HUP;
	else if(termResult != 0)
		return SetupUnixSignalHandlersEnumeration::TERM;
	
	return SetupUnixSignalHandlersEnumeration::NONE;
}

int main(int argc, char *argv[]) {
	if(argc != 2) {
		usage(argv[0]);
		return 1;
	}

	RuntimeInformationType rit;
	Configuration::ErrorEnumeration configurationError = rit.loadConfiguration(argv[1]);
	if(configurationError == Configuration::ErrorEnumeration::NONE) {
		QCoreApplication app(argc, argv);

		rit.setPid(app.applicationPid());

		rit.log(QString("SSL info: %1").arg(rit.getConfiguration().getServer().getSsl().toString()));

		Server server(rit);

		switch(setupUnixSignalHandlers()) {
			case SetupUnixSignalHandlersEnumeration::HUP:
				rit.log("Could not initialize HUP signal", true);
			case SetupUnixSignalHandlersEnumeration::TERM:
				rit.log("Could not initialize TERM signal", true);
			case SetupUnixSignalHandlersEnumeration::BOTH:
				rit.log("Could not initialize HUP and TERM signal", true);
			case SetupUnixSignalHandlersEnumeration::NONE:
			default:
				rit.log("HUP and TERM signal initialized");
		}

		/*QObject::connect(
			&server,
			&Server::exit,
			&app,
			&QCoreApplication::exit
		);*/
		if(!server.start()) {
			rit.log("Could not start server", true);
		}

		return app.exec();
	} else {
		rit.log(QString("Startup error: Configuration could not be loaded: %1").arg(Configuration::ErrorEnumerationToString(configurationError)));
	}

	return 2;
}
