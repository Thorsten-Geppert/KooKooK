#include "RuntimeInformationType.h"

RuntimeInformationType::RuntimeInformationType(
) {
}

bool RuntimeInformationType::loadConfiguration(const QString &configurationFilename) {
	return configuration.load(configurationFilename);
}
