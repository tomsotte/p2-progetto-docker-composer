#include "manageruser.h"

const std::string ManagerUser::modelName {"managerUser"};

bool ManagerUser::canEditService() const
{
	return true;
}

bool ManagerUser::canEditVolume() const
{
	return true;
}

bool ManagerUser::canEditNetwork() const
{
	return true;
}

bool ManagerUser::canEditOtherUsers() const
{
	return true;
}

ManagerUser* ManagerUser::clone() const
{
	return new ManagerUser(*this);
}

const std::string&ManagerUser::getModelName() const
{
	return ManagerUser::modelName;
}
