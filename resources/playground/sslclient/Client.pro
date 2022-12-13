QT += core network sql
QT -= gui
TARGET = client

HEADERS += 	Client.h \
			Configuration.h \
			../../../src/modules/lib/Version.h \
			../../../src/modules/lib/Packet.h \
			../../../src/modules/lib/SslSocket.h \
			../../../src/modules/lib/ClientSslSocket.h \
			../../../src/modules/lib/DatabaseLibrary.h

SOURCES += 	main.cpp \
			Client.cpp \
			../../../src/modules/lib/Version.cpp \
			../../../src/modules/lib/Packet.cpp \
			../../../src/modules/lib/SslSocket.cpp \
			../../../src/modules/lib/ClientSslSocket.cpp \
			../../../src/modules/lib/DatabaseLibrary.cpp

