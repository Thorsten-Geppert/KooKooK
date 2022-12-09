#include "Packet.h"

#include <QDebug>

Packet::Packet(
) {
}

Packet::Packet(
	const QString &command,
	const QString &format,
	const uint32_t size,
	const QByteArray &data
) {
	set(command, format, size, data);
}

Packet::Packet(
	const QString &command,
	const QString &format,
	const QByteArray &data
) {
	set(command, format, data);
}

void Packet::set(
	const QString &command,
	const QString &format,
	const uint32_t size,
	const QByteArray &data
) {
	setCommand(command);
	setFormat(format);
	setSize(size);
	setData(data);
}

void Packet::set(
	const QString &command,
	const QString &format,
	const QByteArray &data
) {
	setCommand(command);
	setFormat(format);
	setDataAndSize(data);
}

void Packet::set(const Packet &packet) {
	set(packet.getCommand(), packet.getFormat(), packet.getSize(), packet.getData());
}

void Packet::setCommand(const QString &command) {
	this->command = command;
}

QString Packet::getCommand() const {
	return command;
}

void Packet::setFormat(const QString &format) {
	this->format = format;
}

QString Packet::getFormat() const {
	return format;
}

void Packet::setSize(const uint32_t size) {
	this->size = size;
}

uint32_t Packet::getSize() const {
	return size;
}

void Packet::setData(const QByteArray &data) {
	this->data = data;
}

void Packet::setDataAndSize(const QByteArray &data) {
	setData(data);
	setSize(data.length());
}

QByteArray Packet::getData() const {
	return data;
}

QByteArray &Packet::getDataReference() {
	return data;
}

QByteArray Packet::toByteArray() const {
	QByteArray result;

	const QByteArray delimiter = getDelimiter();

	result.append(getCommand().toUtf8());
	result.append(delimiter);
	result.append(getFormat().toUtf8());
	result.append(delimiter);
	result.append(QByteArray::number(getSize()));
	result.append(delimiter);
	result.append(getData());

	return result;
}

Packet Packet::parse(
	const QByteArray &packet,
	const QByteArray &delimiter,
	Packet::ErrorType *errorType
) {
	Packet tmp;

	ErrorType tmpErrorType = ErrorType::NONE;

	const qsizetype packetSize = packet.size();

	if(packetSize > 0) {
		if(packet.count(delimiter) >= 3) {
			const qsizetype commandEnd = packet.indexOf(delimiter, 0);
			if(commandEnd >= 0) {
				const qsizetype formatEnd = packet.indexOf(delimiter, commandEnd + 1);
				if(formatEnd > 0) {
					const qsizetype sizeEnd = packet.indexOf(delimiter, formatEnd + 1);
					if(sizeEnd > 0) {
						const QByteArray command = packet.sliced(0, commandEnd);
						const QByteArray format  = packet.sliced(commandEnd + 1, formatEnd - commandEnd - 1);
						const QByteArray size    = packet.sliced(formatEnd + 1, sizeEnd - formatEnd - 1);
						const QByteArray data    = packet.right(packetSize - sizeEnd - 1);

						tmp.setCommand(command);
						tmp.setFormat(format);
						tmp.setData(data);

						bool sizeConvert = false;
						tmp.setSize(size.toUInt(&sizeConvert));

						if(command.isEmpty() || format.isEmpty() || size.isEmpty())
							tmpErrorType = ErrorType::FIELDS;
						else if(!sizeConvert)
							tmpErrorType = ErrorType::SIZE_CONVERT;
					} else {
						tmpErrorType = ErrorType::SIZE;
					}
				} else {
					tmpErrorType = ErrorType::FORMAT;
				}
			} else {
				tmpErrorType = ErrorType::COMMAND;
			}
		} else {
			tmpErrorType = ErrorType::MALFORMED;
		}
	} else {
		tmpErrorType = ErrorType::EMPTY;
	}

	if(errorType)
		*errorType = tmpErrorType;

	return tmp;
}

Packet::ErrorType Packet::parse(const QByteArray &packet, const bool setOnError) {
	ErrorType errorType = ErrorType::NONE;

	Packet tmp = parse(packet, getDelimiter(), &errorType);
	if(setOnError)
		set(tmp);
	else if(errorType == Packet::ErrorType::NONE)
		set(tmp);
	
	return errorType;
}

void Packet::setDelimiter(const QByteArray &delimiter) {
	this->delimiter = delimiter;
}

QByteArray Packet::getDelimiter() const {
	return delimiter;
}

QString Packet::errorTypeToString(const ErrorType &errorType) {
	QString message;

	switch(errorType) {
		case ErrorType::NONE:         message = "NONE: No error occured"; break;
		case ErrorType::EMPTY:        message = "EMPTY: The transfered string is empty"; break;
		case ErrorType::SIZE:         message = "SIZE: Could not find field 'size'"; break;
		case ErrorType::SIZE_CONVERT: message = "SIZE_CONVERT: Could not convert 'size' to 'unsigned int 32'"; break;
		case ErrorType::COMMAND:      message = "COMMAND: Could not find field 'command'"; break;
		case ErrorType::FORMAT:       message = "FORMAT: Could not find field 'format'"; break;
		case ErrorType::FIELDS:       message = "FIELDS: Not all fields donated"; break;
		case ErrorType::MALFORMED:    message = "MALFORMED: Malformed transfered string"; break;
	}

	return message;
}

bool Packet::isCommand(const QString &command) const {
	return command == getCommand();
}
