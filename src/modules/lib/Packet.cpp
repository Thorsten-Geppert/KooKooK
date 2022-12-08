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

// TODO implement me
QByteArray Packet::toByteArray() const {
	QByteArray result;

	result.append(getCommand().toUtf8());
	result.append("\t");
	result.append(getFormat().toUtf8());
	result.append("\t");
	result.append(QByteArray::number(getSize()));
	result.append("\t");
	result.append("data");

	return result;
}

// TODO Result (ok) to enum (ConvertError, SizeError...)
Packet Packet::parse(const QByteArray &packet, bool *ok) {
	Packet tmp;

	const qsizetype commandEnd = packet.indexOf("\t", 0);
	if(commandEnd >= 0) {
		const qsizetype formatEnd    = packet.indexOf("\t", commandEnd + 1);
		if(formatEnd > 0) {
			const qsizetype sizeEnd  = packet.indexOf("\t", formatEnd + 1);
			if(sizeEnd > 0) {
				const QByteArray command = packet.sliced(0, commandEnd);
				const QByteArray format  = packet.sliced(commandEnd + 1, formatEnd - commandEnd - 1);
				const QByteArray size    = packet.sliced(formatEnd + 1, sizeEnd - formatEnd - 1);
				const QByteArray data    = packet.right(packet.length() - sizeEnd - 1);

				bool sizeConvert = false;

				tmp.setCommand(command);
				tmp.setFormat(format);
				tmp.setSize(size.toUInt(&sizeConvert));
				tmp.setData(data);

				if(ok)
					*ok = sizeConvert;
			}
		}
	}

	return tmp;
}

bool Packet::parse(const QByteArray &packet) {
	bool ok = false;

	Packet tmp = parse(packet, &ok);
	if(ok)
		set(tmp);
	
	return ok;
}
