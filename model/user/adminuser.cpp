#include "adminuser.h"

const std::string AdminUser::modelName = "adminUser";

bool AdminUser::canEditService() const
{
	return true;
}

bool AdminUser::canEditVolume() const
{
	return true;
}

bool AdminUser::canEditNetwork() const
{
	return true;
}

bool AdminUser::canEditOtherUsers() const
{
	return true;
}

bool AdminUser::isAdmin() const
{
	return true;
}

AdminUser *AdminUser::clone() const
{
	return new AdminUser(*this);
}

const std::string& AdminUser::getModelName() const
{
	return AdminUser::modelName;
}
