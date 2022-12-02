#pragma once

#include "ConfigurationType.h"
#include <QString>
#include <QSqlDatabase>

class DatabaseConfigurationType : public ConfigurationType {

	public:
		DatabaseConfigurationType();

		virtual QSqlDatabase create() = 0;

};
