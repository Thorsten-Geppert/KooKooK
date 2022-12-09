#pragma once

#include <QByteArray>
#include <QString>

class Packet {

	public:
		typedef enum class ErrorEnumration : unsigned int {
			NONE = 0,
			EMPTY,
			SIZE,
			SIZE_CONVERT,
			COMMAND,
			FORMAT,
			FIELDS,
			MALFORMED
		} ErrorType;

		Packet();
		Packet(
			const QString &command,
			const QString &format,
			const uint32_t size,
			const QByteArray &data
		);

		Packet(
			const QString &command,
			const QString &format,
			const QByteArray &data
		);

		void set(
			const QString &command,
			const QString &format,
			const uint32_t size,
			const QByteArray &data
		);

		void set(
			const QString &command,
			const QString &format,
			const QByteArray &data
		);

		void set(const Packet &packet);

		void setCommand(const QString &command);
		QString getCommand() const;

		void setFormat(const QString &format);
		QString getFormat() const;

		void setSize(const uint32_t size);
		uint32_t getSize() const;
		
		void setData(const QByteArray &data);
		void setDataAndSize(const QByteArray &data);
		QByteArray getData() const;
		QByteArray &getDataReference();

		QByteArray toByteArray() const;

		static QByteArray getDefaultDelimiter() { return "\t"; }

		static Packet parse(const QByteArray &packet, const QByteArray &delimiter, ErrorType *errorType);
		ErrorType parse(const QByteArray &packet, const bool setOnError = true);

		void setDelimiter(const QByteArray &delimiter);
		QByteArray getDelimiter() const;
		
		static QString errorTypeToString(const ErrorType &errorType);

		bool isCommand(const QString &command) const;
	
	protected:
		QString command;
		QString format;
		uint32_t size = { 0 };
		QByteArray data;
		QByteArray delimiter = getDefaultDelimiter();

};
