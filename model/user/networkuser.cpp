#include "networkuser.h"

const std::string NetworkUser::modelName = "networkUser";

bool NetworkUser::canEditService() const
{
	return true;
}

bool NetworkUser::canEditNetwork() const
{
	return true;
}

NetworkUser*NetworkUser::clone() const
{
	return new NetworkUser(*this);
}

const std::string& NetworkUser::getModelName() const
{
	return NetworkUser::modelName;
}

