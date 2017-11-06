#include "userlist.h"

using std::string;

void UserList::importFromJSON(const nlohmann::json& j)
{
	clear();

    for (const auto& uj : j) { // uj = user json
		addUserFromJSON(uj);
	}
}

User* UserList::findUserByName(const std::string& name) const
{
	for (auto u : list) {
		if (u->getName() == name) return u;
	}

	return nullptr;
}

void UserList::addDefaultAdmin()
{
	try {
		add(new AdminUser("admin", "admin"));
	} catch(UserAlreadyExistsException e) {}
}

void UserList::add(User* t)
{
	if (!findUserByName(t->getName())) DataList<User*>::add(t);
	else throw UserAlreadyExistsException();
}

UserList* UserList::clone() const
{
	return new UserList(*this);
}

User* UserList::createUser(const std::string& r, const std::string& n,
						  const std::string& p)
{
	if (r == CompleteUser::modelName) return new CompleteUser(n, p);
	else if (r == NetworkUser::modelName) return new NetworkUser(n, p);
	else if (r == VolumeUser::modelName) return new VolumeUser(n, p);
	else if (r == AdminUser::modelName) return new AdminUser(n, p);
	else if (r == ManagerUser::modelName) return new ManagerUser(n, p);

	throw std::runtime_error("User type " + r + "not supported.");
}

void UserList::addUserFromJSON(const nlohmann::json& j)
{
	User* u {nullptr};

	try {
		u = UserList::createUser(j["role"], j["name"], j["password"]);

		if (!u) return;

		u->importFromJSON(j);
		add(u);
	} catch(...) {
		// if user has invalid json info or has duplicate name, skips
		// if user already created, delete it
		if (u) delete u;
	}
}
