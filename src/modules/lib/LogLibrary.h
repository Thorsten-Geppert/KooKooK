#pragma once

#include <QObject>
#include <QString>

class LogLibrary : public QObject {

	public:
		LogLibrary(
			QObject *parent = nullptr
		);
		virtual ~LogLibrary();

		virtual bool log(
			const QString &message,
			const bool error = false,
			const qint64 pid = 0
		) = 0;

	protected:
		QString createLogString(
			const QString &message,
			const bool error = false,
			const qint64 pid = 0
		);

};
