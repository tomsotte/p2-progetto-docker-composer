#include "dockerparts.h"

#include <exception>

#include "volumeconfig.h"
#include "networkconfig.h"
#include "serviceconfig.h"
#include "dockerfileconfig.h"

void DockerParts::importFromJSON(const nlohmann::json& j)
{
	for (const auto& jc : j) { // jc = json config
		addDockerPartFromJSON(jc);
	}
}

DockerParts DockerParts::filterByModelName(const std::string& mn) const
{
	DockerParts filtered;

	for (auto elem : list) {
		if (elem->getModelName() != mn) continue;

		filtered.add(elem->clone());
	}

	return filtered;
}

void DockerParts::add(BaseConfig* c)
{
	if (!findConfigByName(c->getName())) DataList::add(c);
	else throw ConfigAlreadyExistsException();
}

DockerParts* DockerParts::clone() const
{
	return new DockerParts(*this);
}

BaseConfig* DockerParts::findConfigByName(const std::string& name)
{
	for (auto elem : list) {
		if (elem->getName() == name) return elem;
	}

	return nullptr;
}

BaseConfig* DockerParts::createDockerPart(const std::string& type,
											  const std::string& name,
											  const std::string& author)
{
	if (type == ServiceConfig::modelName) return new ServiceConfig(name, author);
	else if (type == VolumeConfig::modelName) return new VolumeConfig(name, author);
	else if (type == NetworkConfig::modelName) return new NetworkConfig(name, author);
	else if (type == DockerfileConfig::modelName) return new DockerfileConfig(name, author);

	throw std::runtime_error("Config type " + type + "not supported.");
}

void DockerParts::addDockerPartFromJSON(const nlohmann::json& j)
{
	BaseConfig* c {nullptr};

	try {
		c = createDockerPart(j["_modelName"], j["name"], j["author"]);

		if (!c) return; // skip non-supported models

		c->importFromJSON(j);
		add(c);
	} catch(...) {
		// if created but importJson failed, delete
		if (c) delete c;
	}
}
