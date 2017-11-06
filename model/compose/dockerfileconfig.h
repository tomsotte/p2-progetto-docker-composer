#ifndef DOCKERFILECONFIG_H
#define DOCKERFILECONFIG_H

#include "fileconfig.h"

class DockerfileConfig : public FileConfig
{
public:
	static const std::string modelName;

	// note: name (baseconfig) = filename (fileconfig)
	DockerfileConfig(const std::string& n, const std::string& a)
		: BaseConfig(n, a), FileConfig(n, a, n) {}

	void setText(const std::string& value);

	virtual const std::string& getModelName() const;

	// supports https://docs.docker.com/engine/reference/builder/#dockerfile-examples
	virtual bool validate() const;

	virtual std::string getText() const;

	virtual nlohmann::json exportToJSON() const;
	virtual void importFromJSON(const nlohmann::json& j);

	virtual BaseConfig* clone() const;

	// Exception: the text syntax doesn't follow the rule in line n.
	// syntax rule: "KEYWORD argument" or "# comment" or empty
	class SyntaxErrorLineException : public InvalidConfigException {
	public:
		SyntaxErrorLineException(int l) : line(l) {}
		int line;
	};

private:
	std::string text;
};

#endif // DOCKERFILECONFIG_H
