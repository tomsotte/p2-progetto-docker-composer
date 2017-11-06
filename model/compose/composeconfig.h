#ifndef COMPOSECONFIG_H
#define COMPOSECONFIG_H

#include <map>

#include "yamlconfig.h"
#include "fileconfig.h"

#include "dockerparts.h"

#include "volumeconfig.h"
#include "networkconfig.h"
#include "serviceconfig.h"
#include "dockerfileconfig.h"

class ComposeConfig : public YamlConfig, public FileConfig
{
public:
    static const std::vector<std::string> versions;
	static const std::string modelName;

	ComposeConfig(const std::string& n, const std::string& a, const std::string& f)
		: BaseConfig(n, a), YamlConfig(n, a), FileConfig(n, a, f) {}

	// can be used (r/w) publicly, no const
	DockerParts& getParts();
	const std::string& getVersion() const;

	void setParts(const DockerParts& p);
	void setVersion(const std::string& v);

	void clear();

	virtual bool validate() const;

	virtual const std::string& getModelName() const;

	virtual ComposeConfig* clone() const;

	virtual YAML::YamlFile getYaml() const;
	virtual void importFromJSON(const nlohmann::json& j);
	virtual nlohmann::json exportToJSON() const;

	// Exception: version set is not a supported version (see ComposeConfig::versions)
	class VersionNotSupportedException
			: public BaseConfig::InvalidConfigException {};

private:
	std::string filename;
	std::string version;

	DockerParts parts;

	YAML::YamlFile getPartsYaml(const DockerParts& p) const;
};
#endif // COMPOSECONFIG_H
