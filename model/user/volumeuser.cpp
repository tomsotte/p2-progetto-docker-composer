#include "volumeuser.h"

const std::string VolumeUser::modelName = "volumeUser";

bool VolumeUser::canEditService() const
{
	return true;
}

bool VolumeUser::canEditVolume() const
{
	return true;
}

VolumeUser* VolumeUser::clone() const
{
	return new VolumeUser(*this);
}

const std::string& VolumeUser::getModelName() const
{
	return VolumeUser::modelName;
}
