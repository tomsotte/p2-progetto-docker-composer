#ifndef YAMLCONFIG_H
#define YAMLCONFIG_H

#include "baseconfig.h"
#include "../util/yamlfile.h"

class YamlConfig : public virtual BaseConfig
{
public:
	YamlConfig(const std::string& n, const std::string& a)
		: BaseConfig(n, a) {}

	virtual std::string getText() const;

	// used in getText(); override this in derived classes
	virtual YAML::YamlFile getYaml() const = 0;

	virtual YamlConfig* clone() const = 0;
};

#endif // YAMLCONFIG_H
