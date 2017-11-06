#ifndef ADMINUSER_H
#define ADMINUSER_H

#include "user.h"

// AdminUser is the default user (Core::loadUsers). It has complete access to the app,
// has the level of permissions of CompleteUser and can control, create and remove
// other users.
class AdminUser : public User
{
public:
	static const std::string modelName;

	using User::User;

	virtual bool canEditService() const;
	virtual bool canEditVolume() const;
	virtual bool canEditNetwork() const;
	virtual bool canEditOtherUsers() const;
	virtual bool isAdmin() const;

	virtual AdminUser* clone() const;

	virtual const std::string& getModelName() const;
};

#endif // ADMINUSER_H
