#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <string>
#include "../lib/json.hpp"

class DataModel
{
public:
	static const std::string modelName;

	DataModel() = default;
	virtual ~DataModel() = default;

	virtual const std::string& getModelName() const;

	virtual void importFromJSON(const nlohmann::json& j) = 0;
	virtual nlohmann::json exportToJSON() const = 0;

	virtual DataModel* clone() const = 0;
};

#endif // DATAMODEL_H
