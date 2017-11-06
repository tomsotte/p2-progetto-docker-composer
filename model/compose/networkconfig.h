#ifndef NETWORKCONFIG_H
#define NETWORKCONFIG_H

#include "driverconfig.h"

// https://docs.docker.com/compose/compose-file/#network-configuration-reference
//
//	network-name: std::string (or)
//		driver: string
//		internal: bool (or)
//		external: bool (or)
//			name: string
//		enable_ipv6: bool
//		ipam:
//			driver: string
//			config:
//				subnet: string
class NetworkConfig : public DriverConfig
{
public:
	static const std::string modelName;

	NetworkConfig(const std::string& n, const std::string& a)
		: BaseConfig(n, a), DriverConfig(n, a) {}

	bool getIp6() const;
	bool getInternal() const;
	const std::string& getIpamDriver() const;
	const std::string& getIpamSubnet() const;

	void setIp6(bool value);
	void setInternal(bool value);
	void setIpamDriver(const std::string& value);
	void setIpamSubnet(const std::string& value);

	virtual bool validate() const;

	virtual YAML::YamlFile getYaml() const;
	virtual void importFromJSON(const nlohmann::json& j);
	virtual nlohmann::json exportToJSON() const;

	virtual const std::string& getModelName() const;

	virtual NetworkConfig* clone() const;

	// Exception: if external is set, discard driver and ipam options in output
	class DiscardedDriverAndIpamException
			: public BaseConfig::InvalidConfigException {};

private:
	bool ip6 {false};
	bool internal {false};
	std::string ipamDriver;
	std::string ipamSubnet;
};

#endif // NETWORKCONFIG_H
