HEADERS +=	Defaults.h \
			Server.h \
			Configuration.h \
			RuntimeInformationType.h \
			Protocol.h \
			ProtocolList.h \
			\
			lib/ConfigurationType.h \
			lib/VariantHash.h \
			lib/ServerConfigurationType.h \
			lib/SslConfigurationType.h \
			lib/DatabaseConfigurationType.h \
			lib/SQLServerDatabaseConfigurationType.h \
			lib/PostgreSQLDatabaseConfigurationType.h \
			lib/MySQLDatabaseConfigurationType.h \
			lib/SQLiteDatabaseConfigurationType.h \
			\
			../lib/LogLibrary.h \
			../lib/SystemLogLibrary.h \
			../lib/TextLogLibrary.h \
			../lib/ConsoleLogLibrary.h \
			../lib/Version.h \
			../lib/Packet.h

SOURCES += 	main.cpp \
			Server.cpp \
			Configuration.cpp \
			RuntimeInformationType.cpp \
			Protocol.cpp \
			ProtocolList.cpp \
			\
			lib/ConfigurationType.cpp \
			lib/VariantHash.cpp \
			lib/ServerConfigurationType.cpp \
			lib/SslConfigurationType.cpp \
			lib/DatabaseConfigurationType.cpp \
			lib/SQLServerDatabaseConfigurationType.cpp \
			lib/PostgreSQLDatabaseConfigurationType.cpp \
			lib/MySQLDatabaseConfigurationType.cpp \
			lib/SQLiteDatabaseConfigurationType.cpp \
			\
			../lib/LogLibrary.cpp \
			../lib/SystemLogLibrary.cpp \
			../lib/TextLogLibrary.cpp \
			../lib/ConsoleLogLibrary.cpp \
			../lib/Version.cpp \
			../lib/Packet.cpp

RESOURCES = Server.qrc

QT += network sql
CONFIG += console c++11
Debug:DESTDIR = debug
Release:DESTDIR = release
