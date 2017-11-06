#include "completeuser.h"

const std::string CompleteUser::modelName = "completeUser";

bool CompleteUser::canEditService() const
{
    return true;
}

bool CompleteUser::canEditVolume() const
{
	return true;
}

bool CompleteUser::canEditNetwork() const
{
	return true;
}

CompleteUser* CompleteUser::clone() const
{
	return new CompleteUser(*this);
}

const std::string& CompleteUser::getModelName() const
{
	return CompleteUser::modelName;
}
