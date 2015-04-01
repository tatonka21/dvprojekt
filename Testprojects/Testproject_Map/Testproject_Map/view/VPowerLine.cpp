#include "VPowerLine.h"
#include "VPlayingField.h"

NAMESPACE_VIEW_B 


VPowerLine::VPowerLine(VMaster* vMaster)
: IViewBuilding(vMaster)
{
	m_zm.MakeTextureDiffuse("textures\\_original.jpg");
	m_zg.Init(CHVector(1.5, 2.6, 0.8), &m_zm);
	m_zp.Init();
	m_zp.AddGeo(&m_zg);
}

void VPowerLine::init(const int x, const int y)
{
	vMaster->getPlayingField()->placeObject(this, x, y);
}

NAMESPACE_VIEW_E