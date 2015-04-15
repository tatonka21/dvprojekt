#include "LMaster.h"
#include "LPlayingField.h"
#include "IVMaster.h"
#include "LPlayer.h"

NAMESPACE_LOGIC_B

LMaster::LMaster(IVMaster* vMaster)
	: vMaster(vMaster),
	lPlayer(new LPlayer())
{
	vMaster->registerObserver(this);
}

LMaster::~LMaster()
{
	delete lPlayingField;
	delete lPlayer;
}

void LMaster::startNewGame()
{
	if (lPlayingField == nullptr) {
		lPlayingField = new LPlayingField(this);
	}
}

void LMaster::tick(const float fTimeDelta)
{

}

LPlayingField* LMaster::getLPlayingField()
{
	return lPlayingField;
}

IVMaster* LMaster::getVMaster()
{
	return vMaster;
}

LPlayer* LMaster::getPlayer()
{
	return lPlayer;
}

NAMESPACE_LOGIC_E