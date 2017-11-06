#ifndef USERLIST_H
#define USERLIST_H

#include "user.h"
#include "completeuser.h"
#include "networkuser.h"
#include "volumeuser.h"
#include "adminuser.h"
#include "manageruser.h"

#include "../datalist.h"

class UserList : public DataList<User*>
{
public:	
	using DataList::DataList;

	User* findUserByName(const std::string& name) const;
	void addDefaultAdmin();

	virtual void add(User *t);

	virtual UserList* clone() const;

	virtual void importFromJSON(const nlohmann::json& j);

	// Factory method to create a user based on the info passed
	// This way, the user created can be temporary and added to the userlist later on
	static User* createUser(const std::string& r, const std::string& n,
							const std::string& p);

	// Exception: an user with the same name already exist in the userlist
	class UserAlreadyExistsException {};

private:
	void addUserFromJSON(const nlohmann::json& j);
};

#endif // USERLIST_H
