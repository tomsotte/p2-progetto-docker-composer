#include "jsonutil.h"

std::vector<std::string> nlohmann::toStringVector(const nlohmann::json& j)
{
	std::vector<std::string> v;

	// elem is a string in a json array
	for (const auto& elem : j) {
		v.push_back(elem);
	}

	return v;
}



std::map<std::string, std::string> nlohmann::toStringMap(const nlohmann::json& j)
{
	std::map<std::string, std::string> m;

	// every pair<key,value> in a json object
	for (auto it = j.begin(); it != j.end(); ++it) {
		m[it.key()] = it.value();
	}

	return m;
}
