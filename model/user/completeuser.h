#ifndef COMPLETEUSER_H
#define COMPLETEUSER_H

#include "user.h"

// CompleterUser has the complete access to the docker functionality, and can edit
// both networks and volumes, other than services.
// For example it can create a full web stack (web + db + other services)
class CompleteUser : public User
{
public:
	static const std::string modelName;

	using User::User;

	virtual bool canEditService() const;
	virtual bool canEditVolume() const;
	virtual bool canEditNetwork() const;

	virtual CompleteUser* clone() const;

	virtual const std::string& getModelName() const;
};

#endif // COMPLETEUSER_H
