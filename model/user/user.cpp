#include "user.h"

const std::string& User::getName() const
{
    return name;
}

void User::setName(const std::string& value)
{
	name = value;
}

const std::string& User::getPassword() const
{
	return password;
}

void User::setPassword(const std::string& value)
{
	password = value;
}

bool User::checkPassword(const std::string& p) const
{
	return p == password;
}

bool User::canEditService() const
{
	return false;
}

bool User::canEditNetwork() const
{
	return false;
}

bool User::canEditVolume() const
{
	return false;
}

bool User::canEditOtherUsers() const
{
	return false;
}

bool User::isAdmin() const
{
	return false;
}

std::string User::getRole() const
{
	return getModelName();
}

void User::importFromJSON(const nlohmann::json& j)
{
	// will be used for future info extensions on the user
}

nlohmann::json User::exportToJSON() const
{
	nlohmann::json j;

	j["name"] = name;
	j["password"] = password;
	j["role"] = getRole();

	return j;
}

bool User::operator==(const User& u) const
{
	return name == u.name;
}
