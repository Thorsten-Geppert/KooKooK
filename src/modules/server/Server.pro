HEADERS +=	Server.h \
			ServerThread.h \
			ServerThreadList.h \
			ServerThreadManager.h \
			Configuration.h \
			RuntimeInformationType.h \
			\
			lib/ConfigurationType.h \
			lib/VariantHash.h \
			lib/ServerConfigurationType.h

SOURCES += 	main.cpp \
			Server.cpp \
			ServerThread.cpp \
			ServerThreadList.cpp \
			ServerThreadManager.cpp \
			Configuration.cpp \
			RuntimeInformationType.cpp \
			\
			lib/ConfigurationType.cpp \
			lib/VariantHash.cpp \
			lib/ServerConfigurationType.cpp

QT += network
CONFIG += console c++11
Debug:DESTDIR = debug
Release:DESTDIR = release
