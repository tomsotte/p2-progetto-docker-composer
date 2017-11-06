#include <sstream>
#include <exception>

#include "yamlfile.h"

using std::string;

namespace YAML {

void YamlFile::indent()
{
	indentLevel++;
}

void YamlFile::unindent()
{
	indentLevel--;

	// not meant to be catched but to be fixed in the program
	if (indentLevel < 0) throw std::logic_error("indent level below root!");
}


void YamlFile::addLine(const string& s)
{
	// prefix a number of tabs equal to the current indentLevel
	lines.push_back(string(indentLevel, '\t') + s);
}

// adds one empty key, which can be empty
YamlFile& YamlFile::operator<<(const string& key)
{
	addLine(key + ':');
	indent();
	return *this;
}

YamlFile& YamlFile::operator<<(const YKeyValue kv)
{
	addLine(kv.first + ": " + kv.second);
	return *this;
}

YamlFile& YamlFile::operator<<(const YKeyMap km)
{
	*this << km.first; // will indent

	for (auto const& p : km.second)	{
		*this << p;
	}

	*this << Key::close;
	return *this;
}

YamlFile& YamlFile::operator<<(const YKeyList kl)
{
	*this << kl.first; // will indent

	for (const string& s : kl.second) addLine("- " + s);

	*this << Key::close;
	return *this;
}

YamlFile& YamlFile::operator<<(const YamlFile& y)
{
	for (const string& s : y.lines) addLine(s);

	return *this;
}

YamlFile& YamlFile::operator<<(Key key)
{
	switch (key) {
		case Key::close: unindent(); break;
		case Key::reopen: indent(); break;
		default: break;
	}

	return *this;
}

void YamlFile::clear()
{
	lines.clear();
	indentLevel = 0;
}

string YamlFile::getText() const
{
	std::stringstream oss;

	if (lines.empty()) return string();

	for (const string& l : lines) {
		oss << l << std::endl;
	}

	return oss.str();
}

} // namespace YAML
