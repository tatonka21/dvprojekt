#pragma once
#include "ILPowerPlant.h"
class LOilRefinery :
	public ILPowerPlant
{
public:
	LOilRefinery(const int costs, const int energyValue, LPlayingField* playingField, const int x, const int y);
	~LOilRefinery();
};

