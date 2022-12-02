#pragma once

#include "LogLibrary.h"

class TextLogLibrary : public LogLibrary {

	public:
		TextLogLibrary(
			const QString &logFilename,
			const bool fallbackToSyslog = true,
			QObject *parent = nullptr
		);

		virtual bool log(
			const QString &message,
			const bool error = false,
			const qint64 pid = 0
		) override;

		void setLogFilename(const QString &logFilename);
		QString getLogFilename() const;

		void setFallbackToSyslog(const bool fallbackToSyslog);
		bool getFallbackToSyslog() const;
	
	protected:
		QString logFilename;
		bool fallbackToSyslog = true;

};
