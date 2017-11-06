#include "baseconfig.h"

const std::string& BaseConfig::getAuthor() const
{
	return author;
}

void BaseConfig::setAuthor(const std::string& value)
{
	author = value;
}

const std::string& BaseConfig::getName() const
{
	return name;
}

void BaseConfig::setName(const std::string &value)
{
	name = value;
}

nlohmann::json BaseConfig::exportToJSON() const
{
	nlohmann::json j;

	j["_modelName"] = getModelName();
	j["author"] = getAuthor();
	j["name"] = getName();

	return j;
}
