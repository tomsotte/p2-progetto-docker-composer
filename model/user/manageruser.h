#ifndef MANAGERUSER_H
#define MANAGERUSER_H

#include "user.h"

// ManagerUser has all the possibilities of the complete user, but can also edit
// others work.
class ManagerUser : public User
{
public:
	static const std::string modelName;

	using User::User;

	virtual bool canEditService() const;
	virtual bool canEditVolume() const;
	virtual bool canEditNetwork() const;
	virtual bool canEditOtherUsers() const;

	virtual ManagerUser* clone() const;

	virtual const std::string& getModelName() const;
};

#endif // MANAGERUSER_H
