#pragma once

#include <QString>

class Version {

	public:
		Version();
		Version(
			const unsigned int major,
			const unsigned int minor,
			const unsigned int patch
		);
		Version(const QString &version);

		void set(
			const unsigned int major,
			const unsigned int minor,
			const unsigned int patch
		);
		bool set(const QString &version);
		bool set(
			const QString &major,
			const QString &minor,
			const QString &patch
		);
		void set(const Version &version);

		void setMajor(const unsigned int major);
		unsigned int getMajor() const;

		void setMinor(const unsigned int minor);
		unsigned int getMinor() const;

		void setPatch(const unsigned int patch);
		unsigned int getPatch() const;

		QString toString();

		static Version parseVersion(const QString &version, bool &ok);
	
	private:
		unsigned int major = { 0 };
		unsigned int minor = { 0 };
		unsigned int patch = { 0 };

};
