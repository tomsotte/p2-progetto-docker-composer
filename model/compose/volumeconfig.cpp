#include "volumeconfig.h"

const std::string VolumeConfig::modelName {"volume"};

const std::string& VolumeConfig::getModelName() const
{
	return VolumeConfig::modelName;
}

VolumeConfig* VolumeConfig::clone() const
{
	return new VolumeConfig(*this);
}
