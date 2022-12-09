QT += core network sql
QT -= gui
TARGET = client

HEADERS += 	Client.h \
			Configuration.h \
			../../../src/modules/lib/Version.h \
			../../../src/modules/lib/Packet.h \
			../../../src/modules/server/Protocol.h

SOURCES += 	main.cpp \
			Client.cpp \
			../../../src/modules/lib/Version.cpp \
			../../../src/modules/lib/Packet.cpp \
			../../../src/modules/server/Protocol.cpp

