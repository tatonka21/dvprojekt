#pragma once
#include "LField.h"
#include "IVPlayingField.h"
#include "LMaster.h"

//todo:  Methoden fuer abreissen und Upgrade
class LPlayingField
{

private:
	LMaster* lMaster;
	IVPlayingField* vField;
	LField * fieldArray;
	int fieldLength;

public:
	LPlayingField(LMaster* lMaster)
		: lMaster(lMaster)
	{
		vField->init();
	}
	LPlayingField(const int length); //length = Kantenlšnge des quadratischen Spielfeldes
	~LPlayingField();

	LField & getField(int i, int j);
};
