#ifndef CORE_H
#define CORE_H

#include <string>

#include "user/userlist.h"
#include "compose/composeconfig.h"

class Core
{
public:
	Core() = default;
	~Core();

	User* getLoggedUser() const;
	UserList* getUsers() const;
	ComposeConfig* getCompose() const;

	void setLoggedUser(User* value);

	void loadUsers();
	void loadCompose(const std::string& filePath = "docker-compose.yml");

	void saveUsers() const;
	void saveCompose() const;

private:
	User* loggedUser {nullptr};

	UserList* users {nullptr};
	ComposeConfig* compose {nullptr};
};

#endif // CORE_H
