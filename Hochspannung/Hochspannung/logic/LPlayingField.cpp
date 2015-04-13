#include "LPlayingField.h"
#include "LPlayer.h"
#include "ILBuilding.h"
#include "LMaster.h"
#include "IVPlayingField.h"
#include "IVMaster.h"
#include "IVFactory.h"

LPlayingField::LPlayingField(LMaster* lMaster)
: lMaster(lMaster), fieldArray(fieldLength, fieldLength, [this](LField& obj)
{   //Lambda-Expression
	obj.setLPlayingField(this);
	//TODO (MB) create fields randomly with city
	
	createFields();
	
		//TODO (MB) create LCity --> placeBuilding
		obj.init(LField::WATER, LField::LEVEL1);
	})
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
	if (getField(x, y)->removeBuilding()) {
		vPlayingField->objectRemoved(x, y);
	}
	else {
		//TODO (All) how to handle error checks?
	}
}

void LPlayingField::upgradeBuilding(const int x, const int y)
{
	if (lMaster->getPlayer()->getMoney() > 50000)
	{
		getField(x, y)->getBuilding()->upgrade();
	}
	// ToDo (FL) Discuss case player doesn't have enough money
}

void LPlayingField::createFields()
{
	LField::FieldType fieldTypes[6] { LField::FieldType::CITY, LField::FieldType::COAL, LField::FieldType::GRASS, LField::FieldType::MOUNTAIN, LField::FieldType::OIL, LField::FieldType::WATER};
	LField::FieldLevel fieldLevels[3] { LField::FieldLevel::LEVEL1, LField::FieldLevel::LEVEL2, LField::FieldLevel::LEVEL3};

	for (int x = 0; x < fieldLength; x++)
	{
		for (int y = 0; y < fieldLength; y++)
		{

			int type = rand() % 5;
			int level = rand() % 3;

			LField field;
			field.init(fieldTypes[type], fieldLevels[level]);
			fieldArray[x][y] = field;
		}
	}

}

LMaster* LPlayingField::getLMaster()
{
	return lMaster;
}