#include "LPlayingField.h"
#include "LCoalPowerPlant.h"
#include "LPlayer.h"

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

void LPlayingField::placeBuilding(const int x, const int y)
{
	//todo (IP) just for testing, parameter needs to be added (which building has to be build?)
	LCoalPowerPlant* tempPlant = new LCoalPowerPlant(100, 20, this, x, y);
	getField(x,y)->setBuilding(tempPlant);
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