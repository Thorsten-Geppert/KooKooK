HEADERS +=	Defaults.h \
			Server.h \
			ServerThread.h \
			ServerThreadList.h \
			ServerThreadManager.h \
			Configuration.h \
			RuntimeInformationType.h \
			\
			lib/ConfigurationType.h \
			lib/VariantHash.h \
			lib/ServerConfigurationType.h \
			lib/DatabaseConfigurationType.h \
			lib/SQLServerDatabaseConfigurationType.h \
			lib/PostgreSQLDatabaseConfigurationType.h \
			lib/MySQLDatabaseConfigurationType.h \
			lib/SQLiteDatabaseConfigurationType.h \
			\
			../lib/LogLibrary.h \
			../lib/SystemLogLibrary.h \
			../lib/TextLogLibrary.h \
			../lib/ConsoleLogLibrary.h

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
			lib/ServerConfigurationType.cpp \
			lib/DatabaseConfigurationType.cpp \
			lib/SQLServerDatabaseConfigurationType.cpp \
			lib/PostgreSQLDatabaseConfigurationType.cpp \
			lib/MySQLDatabaseConfigurationType.cpp \
			lib/SQLiteDatabaseConfigurationType.cpp \
			\
			../lib/LogLibrary.cpp \
			../lib/SystemLogLibrary.cpp \
			../lib/TextLogLibrary.cpp \
			../lib/ConsoleLogLibrary.cpp

QT += network sql
CONFIG += console c++11
Debug:DESTDIR = debug
Release:DESTDIR = release
