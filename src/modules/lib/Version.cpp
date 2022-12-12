#include "Version.h"
#include <QStringList>
#include <QRegularExpression>

Version::Version() {
}

Version::Version(const QString &version) {
	set(version);
}

Version::Version(
	const unsigned int major,
	const unsigned int minor,
	const unsigned int patch
) {
	set(major, minor, patch);
}

void Version::setMajor(const unsigned int major) {
	this->major = major;
}

unsigned int Version::getMajor() const {
	return major;
}

void Version::setMinor(const unsigned int minor) {
	this->minor = minor;
}

unsigned int Version::getMinor() const {
	return minor;
}

void Version::setPatch(const unsigned int patch) {
	this->patch = patch;
}

unsigned int Version::getPatch() const {
	return patch;
}

QString Version::toString() {
	return QString("%1.%2.%3").arg(getMajor()).arg(getMinor()).arg(getPatch());
}

bool Version::set(const QString &version) {
	bool ok = false;
	
	set(parseVersion(version, ok));

	return ok;
}

Version Version::parseVersion(const QString &version, bool &ok) {
	ok = false;

	Version result;

	QRegularExpressionMatch match = QRegularExpression(
		"^(?<major>\\d*)\\.(?<minor>\\d*)\\.(?<patch>\\d*)$"
	).match(version);
	ok = match.hasMatch();
	if(ok)
		result.set(
			match.captured("major"),
			match.captured("minor"),
			match.captured("patch")
		);

	return result;
}

void Version::set(
	const unsigned int major,
	const unsigned int minor,
	const unsigned int patch
) {
	setMajor(major);
	setMinor(minor);
	setPatch(patch);
}

bool Version::set(
	const QString &major,
	const QString &minor,
	const QString &patch
) {
	bool majorOk = false;
	bool minorOk = false;
	bool patchOk = false;
	
	const unsigned int majorInt = major.toInt(&majorOk);
	const unsigned int minorInt = minor.toInt(&minorOk);
	const unsigned int patchInt = patch.toInt(&patchOk);

	setMajor(majorInt);
	setMinor(minorInt);
	setPatch(patchInt);

	return majorOk && minorOk && patchOk;
}

void Version::set(const Version &version) {
	setMajor(version.getMajor());
	setMinor(version.getMinor());
	setPatch(version.getPatch());
}

Version Version::operator=(const QString &value) {
	return Version(value);
}
