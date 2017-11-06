#include "datamodel.h"

const std::string DataModel::modelName {"abstract"};

const std::string& DataModel::getModelName() const
{
	return modelName;
}
