#ifndef DRIVERCONFIG_H
#define DRIVERCONFIG_H

#include "yamlconfig.h"

// Common driver part between network and volume configs
// https://docs.docker.com/compose/compose-file/#volume-configuration-reference
// https://docs.docker.com/compose/compose-file/#network-configuration-reference
// (Note: labels are rarely used)
//
//	driver-name: string (or)
//		driver: string
//		external: bool (or)
//			name: string
class DriverConfig : public YamlConfig
{
public:
	DriverConfig(const std::string& n, const std::string& a)
		: BaseConfig(n, a), YamlConfig(n, a) {}

	bool getExternal() const;
	const std::string& getExternalName() const;
	const std::string& getDriver() const;

	void setExternal(bool value);
	void setExternalName(const std::string& value);
	void setDriver(const std::string& value);

	virtual bool validate() const;

	virtual YAML::YamlFile getYaml() const;
	virtual void importFromJSON(const nlohmann::json& j);
	virtual nlohmann::json exportToJSON() const;

	// Exception: If external is set, discard driver option in output
	class DiscardedDriverException
			: public BaseConfig::InvalidConfigException {};

protected:
	std::string driver;
	bool external {false};
	std::string externalName;
};

#endif // DRIVERCONFIG_H
