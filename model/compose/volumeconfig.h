#ifndef VOLUMECONFIG_H
#define VOLUMECONFIG_H

#include "driverconfig.h"

// https://docs.docker.com/compose/compose-file/#volume-configuration-reference
// (it's the same as the base, DriverConfig)
//
//	volume-name: string (or)
//		driver: string
//		external: bool (or)
//			name: string
class VolumeConfig : public DriverConfig
{
public:
	static const std::string modelName;

	VolumeConfig(const std::string& n, const std::string& a)
		: BaseConfig(n, a), DriverConfig(n, a) {}

	virtual const std::string& getModelName() const;

	virtual VolumeConfig* clone() const;
};

#endif // VOLUMECONFIG_H
