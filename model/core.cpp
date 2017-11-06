#include "core.h"

#include <iostream>
#include <fstream>

#include "../lib/json.hpp"

const std::string usersFile {"users.json"};

void Core::loadUsers()
{
	std::ifstream file(usersFile);
	nlohmann::json j;

	UserList* newUsers {nullptr};

	try {
		file >> j;
		newUsers = new UserList();
		newUsers->importFromJSON(j);
	} catch(...) {
		// if there are any errors in reading or importing, create new users list
		if (newUsers) delete newUsers;
		newUsers = new UserList();
	}

	// always add a default admin/admin user
	newUsers->addDefaultAdmin();

	if (users) delete users;
	users = newUsers;

	saveUsers();
}

void Core::loadCompose(const std::string& filePath)
{
	std::ifstream file(filePath + ".json");
	nlohmann::json j;

	ComposeConfig* newCompose {nullptr};

	try {
		file >> j;
		newCompose = new ComposeConfig(j["name"], j["author"], filePath);
		newCompose->importFromJSON(j);
	} catch(...) {
		// if there are any errors in reading or importing, create new compose
		if (newCompose) delete newCompose;
		newCompose = new ComposeConfig("", "", filePath);
	}

	// overwrite the previous compose, if any, set the new and save
	if (compose) delete compose;
	compose = newCompose;

	saveCompose();
}

void Core::saveUsers() const
{
	if (!users) return;

	std::ofstream file(usersFile);
	file << users->exportToJSON().dump(4);
}

void Core::saveCompose() const
{
	if (!compose) return;

	std::ofstream file(compose->getFilename() + ".json");
	file << compose->exportToJSON().dump(4);
}

UserList* Core::getUsers() const
{
	return users;
}

ComposeConfig* Core::getCompose() const
{
	return compose;
}

Core::~Core()
{
	delete users;
	delete loggedUser;
	delete compose;
}

User* Core::getLoggedUser() const
{
    return loggedUser;
}

void Core::setLoggedUser(User* value)
{
    loggedUser = value;

	// get ownership of the compose file if just created
	if (compose->getAuthor().empty()) compose->setAuthor(loggedUser->getName());
	if (compose->getName().empty()) compose->setName("compose");
}
