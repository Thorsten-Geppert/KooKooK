#!/usr/bin/env bash

#QMAKE="/Users/thorsten/Qt/6.4.1/macos/bin/qmake6"
QMAKE=qmake6
LAST_PATH="`pwd`"
COMPILE_PATH="`dirname $0`/build"

if [ $# -gt 0 ]
then
	if [[ $1 == "--clean" ]]
	then
		test -d "${COMPILE_PATH}" && rm -Rf "${COMPILE_PATH}"
	else
		echo "Usage: ${0} [--clean | --help]"
	fi
else
	if [ ! -d "${COMPILE_PATH}" ]
	then
		mkdir -p "${COMPILE_PATH}"
		if [ $? != 0 ]
		then
			echo "Could not create build directory ${COMPILE_PATH}"
			exit 1
		fi
	fi

	cd "${COMPILE_PATH}"
	"${QMAKE}" ../ && make
	cd "${LAST_PATH}"
fi
