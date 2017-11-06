#ifndef VOLUMEUSER_H
#define VOLUMEUSER_H

#include "user.h"

// VolumeUser is a user that can edit (r/w) volumes and services
// For example, this user can setup an offline/local service which uses
// local data storage, like databases.
class VolumeUser : public User
{
public:
	const static std::string modelName;

	using User::User;

	virtual bool canEditService() const;
	virtual bool canEditVolume() const;

	virtual VolumeUser* clone() const;

	virtual const std::string& getModelName() const;
};

#endif // VOLUMEUSER_H
