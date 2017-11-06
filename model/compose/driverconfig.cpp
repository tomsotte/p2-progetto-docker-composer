#include "driverconfig.h"

using namespace YAML;

YamlFile DriverConfig::getYaml() const
{
	YamlFile yaml;

	yaml << name;

	if (external) {
		if (externalName.empty()) {
			yaml << YKeyValue("external", "true");
		} else {
			yaml << "external" << YKeyValue("name", externalName) << Key::close;
		}
	} else if (!driver.empty()){
		yaml << YKeyValue("driver", driver);
	}

	yaml << Key::close;

	return yaml;
}

void DriverConfig::importFromJSON(const nlohmann::json& j)
{
	external = j["external"];
	externalName = j["externalName"];
	driver = j["driver"];
}

nlohmann::json DriverConfig::exportToJSON() const
{
	nlohmann::json j(YamlConfig::exportToJSON());

	j["external"] = external;
	j["externalName"] = externalName;
	j["driver"] = driver;

	return j;
}

const std::string& DriverConfig::getDriver() const
{
	return driver;
}

void DriverConfig::setDriver(const std::string& value)
{
	driver = value;
}

bool DriverConfig::getExternal() const
{
	return external;
}

void DriverConfig::setExternal(bool value)
{
	external = value;
}

const std::string& DriverConfig::getExternalName() const
{
	return externalName;
}

void DriverConfig::setExternalName(const std::string& value)
{
	externalName = value;
}

bool DriverConfig::validate() const
{
	if (external && !driver.empty()) throw DiscardedDriverException();
	return true;
}
