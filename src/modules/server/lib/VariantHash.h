#pragma once

#include <QHash>
#include <QString>
#include <QVariant>

class VariantHash : public QHash<QString, QVariant> {

	public:
		VariantHash();

};
