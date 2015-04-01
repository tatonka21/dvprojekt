#include "LPlayingField.h"
#include "LPlayer.h"
#include "LCoalPowerPlant.h"
#include "LMaster.h"
#include "IVPlayingField.h"
#include "IVMaster.h"
#include "IVFactory.h"

LPlayingField::LPlayingField(LMaster* lMaster)
	: lMaster(lMaster), fieldArray(fieldLength, fieldLength)
{
	vPlayingField = this->lMaster->getVMaster()->getFactory()->createPlayingField(this);
}

LPlayingField::~LPlayingField()
{
	delete vPlayingField;
}

void LPlayingField::initVPlayingField()
{
	vPlayingField->initPlayingField();
}

LField* LPlayingField::getField(const int x, const int y)
{
	return &fieldArray[x][y];
}

int LPlayingField::getFieldLength()
{
	return fieldLength;
}

void LPlayingField::removeBuilding(const int x, const int y)
{
	LField * selectedField = getField(x,y);
	delete selectedField->getBuilding();
	selectedField->setBuilding(nullptr);
}


void LPlayingField::upgradeBuilding(const int x, const int y)
{
	LPlayer* selectedPlayer = lMaster->getPlayer();
	if (selectedPlayer->getMoney() > 50000)
	{
		LField * selectedField = &fieldArray[x][y];
		selectedField->getBuilding()->upgrade();
	}
	// ToDo (FL) Discuss case player dont have enough money
}

LMaster* LPlayingField::getLMaster()
{
	return lMaster;
}