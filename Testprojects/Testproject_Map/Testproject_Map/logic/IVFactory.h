#pragma once

class IVPlayingField;
class LPlayingField;
class IVPowerPlant;
class LCoalPowerPlant;
class LHydroelectricPowerPlant;

class IVFactory
{
public:
	IVFactory()
	{}
	virtual ~IVFactory(){};
	virtual IVPlayingField* createPlayingField(LPlayingField* field) = 0;
	virtual IVPowerPlant* createCoalPowerPlant(LCoalPowerPlant* powerPlant) = 0;
	virtual IVPowerPlant* createHydroelectricPowerPlant(LHydroelectricPowerPlant* powerPlant) = 0;
};

