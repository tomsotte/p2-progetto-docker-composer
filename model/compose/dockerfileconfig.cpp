#include "dockerfileconfig.h"
#include "../util/stringutil.h"

//#include <QString>
//#include <QStringList>
//#include <QRegExp>

#include <regex>

const std::string DockerfileConfig::modelName {"dockerfile"};

bool DockerfileConfig::validate() const
{
	// v1: (^#.*)|(^[A-Z]+ .+)|(^(\n|\s(?!\w)))
	// supports empty lines
	// v2: (^#.*)|(^[A-Z]+ .+)|(^(\\n|\\s|\\r))
	// better empty lines support
	std::regex syntax("(^#.*)|(^[A-Z]+ .+)|(^(\\n|\\s|\\r))");

	auto lines = StringUtil::split(text, '\n');

	for (unsigned int i = 0; i < lines.size(); ++i) {
		if (lines[i].empty()) continue;
		if (!std::regex_match(lines[i], syntax)) throw SyntaxErrorLineException(i);
	}

	return true;
}

std::string DockerfileConfig::getText() const
{
	return text;
}

nlohmann::json DockerfileConfig::exportToJSON() const
{
	nlohmann::json j(BaseConfig::exportToJSON());

	j["text"] = getText();

	return j;
}

void DockerfileConfig::importFromJSON(const nlohmann::json& j)
{
	text = j["text"];
}

BaseConfig* DockerfileConfig::clone() const
{
	return new DockerfileConfig(*this);
}

void DockerfileConfig::setText(const std::string& value)
{
	text = value;
}

const std::string& DockerfileConfig::getModelName() const
{
	return DockerfileConfig::modelName;
}
