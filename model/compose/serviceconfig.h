#ifndef SERVICECONFIG_H
#define SERVICECONFIG_H

#include "yamlconfig.h"

// https://docs.docker.com/compose/compose-file/#service-configuration-reference
// BuildContext or Image are required otherwise the compose file would be invalid.
//
//	service-name: string
//		image: string (or)
//		build: string
//		ports:
//			- port (or) port:port (or) port-range
//		links:
//			- ServiceConfig:alias
//		networks:
//			- NetworkConfig
//		volumes: (short-syntax)
//			- path (or) path:path (or) VolumeConfig:path
//		environment:
//			- key=value
class ServiceConfig : public YamlConfig
{
public:
	static const std::string modelName;

	ServiceConfig(const std::string& n, const std::string& a)
		: BaseConfig(n, a), YamlConfig(n, a) {}

	const std::string& getImage() const;
	const std::string& getContainerName() const;
	const std::string& getBuildContext() const;
	const std::string& getBuildDockerfile() const;
	const std::vector<std::string>& getPorts() const;
	const std::vector<std::string>& getEnvironment() const;
	const std::vector<std::string>& getLinks() const;
	const std::vector<std::string>& getNetworks() const;
	const std::vector<std::string>& getVolumes() const;

	void setImage(const std::string& value);
	void setBuildContext(const std::string& value);
	void setBuildDockerfile(const std::string& value);
	void setContainerName(const std::string& value);

	void setLinks(const std::vector<std::string>& value);
	void setNetworks(const std::vector<std::string>& value);
	void setVolumes(const std::vector<std::string>& value);
	void setPorts(const std::vector<std::string>& value);
	void setEnvironment(const std::vector<std::string>& value);

    virtual bool validate() const;

	virtual const std::string& getModelName() const;

	virtual YAML::YamlFile getYaml() const;
	virtual void importFromJSON(const nlohmann::json& j);
	virtual nlohmann::json exportToJSON() const;

	virtual ServiceConfig* clone() const;

	// Exception: At least image or buildContext has to be set
	class EmptyImageOrBuildException
			: public BaseConfig::InvalidConfigException {};

private:
	std::string image;
	std::string buildContext;
	std::string buildDockerfile;

	std::string containerName;
	std::vector<std::string> ports;
	std::vector<std::string> environment;
	std::vector<std::string> links;
	std::vector<std::string> networks;
	std::vector<std::string> volumes;
};

#endif // SERVICECONFIG_H
