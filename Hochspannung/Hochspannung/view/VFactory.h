#pragma once

#include "VGeneral.h"
#include "../logic/IVFactory.h"

NAMESPACE_VIEW_B


class VMaster;

class VFactory : public IVFactory
{
private:
	VMaster* vMaster;

public:
	VFactory(VMaster* vMaster)
		: vMaster(vMaster)
	{}
	virtual ~VFactory()
	{}

	virtual IVPlayingField* createPlayingField(LPlayingField* field);

	virtual std::shared_ptr<IVPowerPlant> createCoalPowerPlant(LCoalPowerPlant* powerPlant);

	virtual std::shared_ptr<IVPowerPlant> createHydroelectricPowerPlant(LHydroelectricPowerPlant* powerPlant);
			
	virtual std::shared_ptr<IVPowerPlant> createNuclearPowerPlant(LNuclearPowerPlant* powerPlant);
			
	virtual std::shared_ptr<IVPowerPlant> createOilRefinery(LOilRefinery* powerplant);
			
	virtual std::shared_ptr<IVPowerPlant> createSolarPowerPlant(LSolarPowerPlant* powerPlant);
			
	virtual std::shared_ptr<IVPowerPlant> createWindmillPowerPlant(LWindmillPowerPlant* powerPlant);

	virtual std::shared_ptr<IVPowerLine> createPowerLine(LPowerLine* powerLine);
};


NAMESPACE_VIEW_E
