#include "fileconfig.h"

std::string FileConfig::getFilename() const
{
	return filename;
}

void FileConfig::setFilename(const std::string& value)
{
	filename = value;
}
