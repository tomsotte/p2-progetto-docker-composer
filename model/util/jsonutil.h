#ifndef JSON_H
#define JSON_H

#include <string>
#include <vector>
#include <map>

#include "../../lib/json.hpp"

namespace nlohmann {

std::vector<std::string> toStringVector(const json& j);
std::map<std::string, std::string> toStringMap(const json& j);

}

#endif // JSON_H
