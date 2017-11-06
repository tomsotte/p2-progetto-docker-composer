#include "networkconfig.h"

using std::string;
using namespace YAML;

const std::string NetworkConfig::modelName {"network"};

const std::string& NetworkConfig::getModelName() const
{
	return NetworkConfig::modelName;
}

YamlFile NetworkConfig::getYaml() const
{
	// external cannot be used in conjunction with other network configuration
	// keys (driver, driver_opts, ipam, internal).

	// extends driver config generated yaml
	YamlFile yaml(DriverConfig::getYaml());
	yaml << Key::reopen;

	if (ip6) yaml << YKeyValue("enable_ipv6", "true");

	// if external, no other key will be added
	// (Note: external and externalName have been already added by DriverConfig::getYaml)
	if (external) {
		yaml << Key::close;
		return yaml;
	}

	if (internal) yaml << YKeyValue("internal", "true");

	if (!ipamDriver.empty()) {
		yaml << "ipam" << YKeyValue("driver", ipamDriver);

		if (!ipamSubnet.empty()) {
			yaml << "config" << YKeyValue("subnet", ipamSubnet) << Key::close;
		}

		yaml << Key::close;
	}

	yaml << Key::close;
	return yaml;
}

void NetworkConfig::importFromJSON(const nlohmann::json& j)
{
	DriverConfig::importFromJSON(j);

	ipamDriver = j["ipamDriver"];
	ipamSubnet = j["ipamSubnet"];
	internal = j["internal"];
	ip6 = j["ip6"];
}

nlohmann::json NetworkConfig::exportToJSON() const
{
	nlohmann::json j(DriverConfig::exportToJSON());

	j["ipamDriver"] = ipamDriver;
	j["ipamSubnet"] = ipamSubnet;
	j["internal"] = internal;
	j["ip6"] = ip6;

	return j;
}

NetworkConfig* NetworkConfig::clone() const
{
	return new NetworkConfig(*this);
}

const std::string& NetworkConfig::getIpamDriver() const
{
	return ipamDriver;
}

void NetworkConfig::setIpamDriver(const string& value)
{
	ipamDriver = value;
}

const std::string& NetworkConfig::getIpamSubnet() const
{
	return ipamSubnet;
}

void NetworkConfig::setIpamSubnet(const string& value)
{
	ipamSubnet = value;
}

bool NetworkConfig::getInternal() const
{
	return internal;
}

void NetworkConfig::setInternal(bool value)
{
	internal = value;
}

bool NetworkConfig::getIp6() const {
	return ip6;
}

void NetworkConfig::setIp6(bool value)
{
	ip6 = value;
}

bool NetworkConfig::validate() const
{
	if (getExternal()
		&& (!ipamDriver.empty() || !ipamSubnet.empty() || !driver.empty()))
	{
		throw DiscardedDriverAndIpamException();
	}

	return true;
}
