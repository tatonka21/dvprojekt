#include "VSolarPowerPlant.h"
#include "VPlayingField.h"
#include "VIdentifier.h"

NAMESPACE_VIEW_B


VSolarPowerPlant::VSolarPowerPlant(VMaster* vMaster, LSolarPowerPlant* lPlant)
	: IViewBuilding(vMaster, &m_zp), IVPowerPlant(lPlant)
{
	m_zm.MakeTextureDiffuse("textures\\_original.jpg");
	m_zg.Init(CHVector(1.5f, 2.6f, 0.8f), &m_zm);
	m_zp.Init();
	m_zp.AddGeo(&m_zg);
}

void VSolarPowerPlant::initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y)
{
	vMaster->getPlayingField()->placeObject(dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);

	SET_NAME_AND_COORDINATES(VIdentifier::VSolarPowerPlant);
}



NAMESPACE_VIEW_E
