#include "composeconfig.h"

#include <algorithm>

using std::string;
using namespace YAML;
using namespace nlohmann;

const std::string ComposeConfig::modelName {"compose"};
const std::vector<std::string> ComposeConfig::versions {"1.0", "2.0", "3.0", "3.3"};

const std::string& ComposeConfig::getModelName() const
{
	return ComposeConfig::modelName;
}

ComposeConfig* ComposeConfig::clone() const
{
	return new ComposeConfig(*this);
}

void ComposeConfig::importFromJSON(const json& j)
{
	version = j["version"];
	parts.importFromJSON(j["parts"]);
}

json ComposeConfig::exportToJSON() const
{
	json j(YamlConfig::exportToJSON());

	j["version"] = version;
	j["parts"] = parts.exportToJSON();

	return j;
}

YamlFile ComposeConfig::getPartsYaml(const DockerParts& p) const
{
	YamlFile y;

	for (const BaseConfig* c : p) {
		if (auto yc = dynamic_cast<const YamlConfig*>(c)) y << yc->getYaml();
	}

	return y;
}

YamlFile ComposeConfig::getYaml() const
{
	YamlFile yaml;

	yaml << YKeyValue("version", getVersion());

	auto services = parts.filterByModelName(ServiceConfig::modelName);
	auto networks = parts.filterByModelName(NetworkConfig::modelName);
	auto volumes = parts.filterByModelName(VolumeConfig::modelName);

	if (!services.empty()) yaml << "services" << getPartsYaml(services) << Key::close;
	if (!networks.empty()) yaml << "networks" << getPartsYaml(networks) << Key::close;
	if (!volumes.empty()) yaml << "volumes" << getPartsYaml(volumes) << Key::close;

	return yaml;
}

void ComposeConfig::clear()
{
	version.clear();
	parts.clear();
}

void ComposeConfig::setParts(const DockerParts& p)
{
	parts = p;
}

DockerParts& ComposeConfig::getParts()
{
	return parts;
}

bool ComposeConfig::validate() const
{
	bool found = std::find(versions.begin(), versions.end(), version) != versions.end();
	if (!found) throw VersionNotSupportedException();

	for (const auto part : parts) part->validate();
	return true;
}

const std::string& ComposeConfig::getVersion() const
{
	return version;
}

void ComposeConfig::setVersion(const std::string& value)
{
	version = value;
}
