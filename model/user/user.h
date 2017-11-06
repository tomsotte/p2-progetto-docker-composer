#ifndef USER_H
#define USER_H

#include <string>

#include "../datamodel.h"

class User : public DataModel
{
public:
	User(const std::string& n, const std::string& p)
		: name(n), password(p) {}

	const std::string& getName() const;
	const std::string& getPassword() const;
	std::string getRole() const; // alias of getModelName()

	void setName(const std::string& value);
	void setPassword(const std::string& value);

	bool checkPassword(const std::string& p) const;

	virtual bool canEditService() const;
	virtual bool canEditNetwork() const;
	virtual bool canEditVolume() const;
	virtual bool canEditOtherUsers() const;
	virtual bool isAdmin() const;

	virtual void importFromJSON(const nlohmann::json& j);
	virtual nlohmann::json exportToJSON() const;

	virtual User* clone() const = 0;
	bool operator==(const User& u) const;

private:
	std::string name;
	std::string password;
};

#endif // USER_H
