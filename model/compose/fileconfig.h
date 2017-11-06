#ifndef FILECONFIG_H
#define FILECONFIG_H

#include "baseconfig.h"

class FileConfig : public virtual BaseConfig
{
public:
	FileConfig(const std::string& n, const std::string& a, const std::string& f)
		: BaseConfig(n, a), filename(f) {}

	std::string getFilename() const;

	void setFilename(const std::string& value);

private:
	std::string filename;
};

#endif // FILECONFIG_H
