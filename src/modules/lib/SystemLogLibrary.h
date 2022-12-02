#pragma once

#include "LogLibrary.h"

class SystemLogLibrary : public LogLibrary {

	public:
		SystemLogLibrary(QObject *parent = nullptr);

		virtual bool log(
			const QString &message,
			const bool error = false,
			const qint64 pid = 0
		) override;

};
