HEADERS += Server.h ServerThread.h ServerThreadList.h ServerThreadManager.h
SOURCES += main.cpp Server.cpp ServerThread.cpp ServerThreadList.cpp ServerThreadManager.cpp
QT += network
CONFIG += console c++11
Debug:DESTDIR = debug
Release:DESTDIR = release
