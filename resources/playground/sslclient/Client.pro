QT += core network
QT -= gui
TARGET = client

HEADERS += 	Client.h \
			Configuration.h \
			../../../src/modules/lib/Version.h \
			../../../src/modules/server/Protocol.h

SOURCES += 	main.cpp \
			Client.cpp \
			../../../src/modules/lib/Version.cpp \
			../../../src/modules/server/Protocol.cpp

