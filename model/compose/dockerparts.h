#ifndef DOCKERPARTS_H
#define DOCKERPARTS_H

#include <exception>

#include "../datalist.h"
#include "baseconfig.h"

class DockerParts : public DataList<BaseConfig*>
{
public:
	BaseConfig* findConfigByName(const std::string& name);

	// Creates a temporary copy of this list, filtered by model name.
	// Used to create separate lists in compose context: services, networks, volumes.
	DockerParts filterByModelName(const std::string& mn) const;

	virtual void add(BaseConfig *c);

	virtual DockerParts* clone() const;

	virtual void importFromJSON(const nlohmann::json& j);

	// Factory method to create new config part
	static BaseConfig* createDockerPart(const std::string& type, const std::string& name,
										const std::string& author);

	class ConfigAlreadyExistsException : public std::exception {};

private:
	void addDockerPartFromJSON(const nlohmann::json& j);
};

#endif // DOCKERPARTS_H
