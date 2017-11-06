#ifndef NETWORKUSER_H
#define NETWORKUSER_H

#include "user.h"

// NetworkUser is the user that can edit (r/w) networks and services
// For example, this user can setup services for a more online/mass oriented use,
// but cannot store data, so the service is for temporary use only, or it can
// link this service to a Database service, which can use volumes.
class NetworkUser : public User
{
public:
	static const std::string modelName;

	using User::User;

	virtual bool canEditService() const;
	virtual bool canEditNetwork() const;

	virtual NetworkUser* clone() const;

	virtual const std::string& getModelName() const;
};

#endif // NETWORKUSER_H
