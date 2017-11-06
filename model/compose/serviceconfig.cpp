#include "serviceconfig.h"

#include "../util/jsonutil.h"

using namespace YAML;

const std::string ServiceConfig::modelName {"service"};

const std::string& ServiceConfig::getModelName() const
{
	return ServiceConfig::modelName;
}

YamlFile ServiceConfig::getYaml() const
{
	YamlFile yaml;

	yaml << name;

	if (!buildContext.empty()) {
		yaml << "build" << YKeyValue("context", buildContext);
		if (!buildDockerfile.empty()) yaml << YKeyValue("dockerfile", buildDockerfile);
		yaml << Key::close;
	}
	if (!containerName.empty()) yaml << YKeyValue("container", containerName);
	if (!environment.empty()) yaml << YKeyList("environment", environment);
	if (!image.empty()) yaml << YKeyValue("image", image);
	if (!links.empty()) yaml << YKeyList("links", links);
	if (!networks.empty()) yaml << YKeyList("networks", networks);
	if (!ports.empty()) yaml << YKeyList("ports", ports);
	if (!volumes.empty()) yaml << YKeyList("volumes", volumes);

	yaml << Key::close;

	return yaml;
}

void ServiceConfig::importFromJSON(const nlohmann::json& j)
{
	image = j["image"];
	containerName = j["containerName"];
	buildContext = j["buildContext"];
	buildDockerfile = j["buildDockerfile"];

	links = nlohmann::toStringVector(j["links"]);
	ports = nlohmann::toStringVector(j["ports"]);
	volumes = nlohmann::toStringVector(j["volumes"]);
	networks = nlohmann::toStringVector(j["networks"]);
	environment = nlohmann::toStringVector(j["environment"]);
}

nlohmann::json ServiceConfig::exportToJSON() const
{
	nlohmann::json j(YamlConfig::exportToJSON());

	j["image"] = image;
	j["containerName"] = containerName;
	j["buildContext"] = buildContext;
	j["buildDockerfile"] = buildDockerfile;

	j["links"] = links;
	j["ports"] = ports;
	j["volumes"] = volumes;
	j["networks"] = networks;
	j["environment"] = environment;

	return j;
}

ServiceConfig* ServiceConfig::clone() const
{
	return new ServiceConfig(*this);
}

const std::string& ServiceConfig::getContainerName() const
{
	return containerName;
}

void ServiceConfig::setContainerName(const std::string& value)
{
	containerName = value;
}

const std::vector<std::string>& ServiceConfig::getPorts() const
{
	return ports;
}

void ServiceConfig::setPorts(const std::vector<std::string>& value)
{
	ports = value;
}

const std::vector<std::string>& ServiceConfig::getEnvironment() const
{
	return environment;
}

void ServiceConfig::setEnvironment(const std::vector<std::string>& value)
{
	environment = value;
}

const std::vector<std::string>& ServiceConfig::getLinks() const
{
	return links;
}

void ServiceConfig::setLinks(const std::vector<std::string>& value)
{
	links = value;
}

const std::vector<std::string>& ServiceConfig::getNetworks() const
{
	return networks;
}

void ServiceConfig::setNetworks(const std::vector<std::string>& value)
{
	networks = value;
}

const std::vector<std::string>& ServiceConfig::getVolumes() const
{
	return volumes;
}

void ServiceConfig::setVolumes(const std::vector<std::string>& value)
{
	volumes = value;
}

const std::string& ServiceConfig::getBuildDockerfile() const
{
	return buildDockerfile;
}

void ServiceConfig::setBuildDockerfile(const std::string& value)
{
	buildDockerfile = value;
}

const std::string& ServiceConfig::getBuildContext() const
{
	return buildContext;
}

void ServiceConfig::setBuildContext(const std::string& value)
{
    buildContext = value;
}

const std::string& ServiceConfig::getImage() const
{
	return image;
}

void ServiceConfig::setImage(const std::string& value)
{
	image = value;
}

bool ServiceConfig::validate() const
{
	if (buildContext.empty() && image.empty()) throw EmptyImageOrBuildException();
	return true;
}
