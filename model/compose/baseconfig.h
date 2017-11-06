#ifndef BASECONFIG_H
#define BASECONFIG_H

#include <string>
#include <exception>
#include "../datamodel.h"

class BaseConfig : public DataModel
{
public:
	// name and author are required
//	BaseConfig() = delete;
	BaseConfig(const std::string& n, const std::string& a)
		: name(n), author(a) {}

	const std::string& getAuthor() const;
	const std::string& getName() const;

	void setAuthor(const std::string& value);
	void setName(const std::string &value);

	// validate a config; usually throws exceptions
    virtual bool validate() const = 0;
	virtual std::string getText() const = 0;

	virtual nlohmann::json exportToJSON() const;
	// import isn't overridden here because the constructor
	// already inits the two members, name and author

	virtual BaseConfig* clone() const = 0;

	// Exception: base invalid config exception, for a catch generic use
	class InvalidConfigException : public std::exception {};

protected:
	std::string name;
	std::string author;
};

#endif // BASECONFIG_H
