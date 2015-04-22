#include "VWindmillPowerPlant.h"
#include "VPlayingField.h"
#include "VIdentifier.h"
#include "VMaster.h"

NAMESPACE_VIEW_B


VWindmillPowerPlant::VWindmillPowerPlant(VMaster* vMaster, LWindmillPowerPlant* lPlant)
	: IVPowerPlant(lPlant), IViewBuilding(vMaster, viewModel.getMainPlacement())
{
	viewModel.getMainPlacement()->RotateX(CASTS<float>(M_PI / 2.0));
	viewModel.getMainPlacement()->RotateZDelta(M_PI);
	viewModel.getMainPlacement()->ScaleDelta(0.8f);
	viewModel.getMainPlacement()->TranslateZDelta(7.0f);

	vMaster->registerObserver(this);
}

VWindmillPowerPlant::~VWindmillPowerPlant()
{}

void VWindmillPowerPlant::initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y)
{
	vMaster->getPlayingField()->placeObject(dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);

	SET_NAME_AND_COORDINATES(VIdentifier::VWindmillPowerPlant);
}




NAMESPACE_VIEW_E
