#ifndef YAMLFILE_H
#define YAMLFILE_H

#include <string>
#include <vector>
#include <list>
#include <map>
#include <utility>

namespace YAML {

using YMap	= std::map<std::string, std::string>;
using YList = std::vector<std::string>;

using YKeyValue = std::pair<std::string, std::string>;
using YKeyMap = std::pair<std::string, const YMap&>;
using YKeyList = std::pair<std::string, const YList&>;

enum class Key { close, reopen };

// Simple Yaml file generator that supports key, list and maps and composition
// Custom tailored to work with this project in mind, so it's not very flexible
// http://www.yaml.org/spec/1.2/spec.html
class YamlFile
{
public:
	YamlFile() = default;

	// add empty open key (can be closed with "<< Key::close")
	YamlFile& operator<<(const std::string& key);

	YamlFile& operator<<(const YKeyValue kv);
	YamlFile& operator<<(const YKeyMap km);	
	YamlFile& operator<<(const YKeyList kl);
	// add a yaml file aligend with the current indentation
	YamlFile& operator<<(const YamlFile& y);

	YamlFile& operator<<(const Key key);

	void clear();

	std::string getText() const;

private:
	int indentLevel {0};
	std::vector<std::string> lines;

	void indent();
	void unindent();
	void addLine(const std::string& s);
};

} // namespace YAML

#endif // YAMLFILE_H

