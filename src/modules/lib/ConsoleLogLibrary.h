#pragma once

#include "LogLibrary.h"

class ConsoleLogLibrary : public LogLibrary {

	public:
		ConsoleLogLibrary(
			QObject *parent = nullptr
		);

		virtual bool log(
			const QString &message,
			const bool error = false
		) override;

};
