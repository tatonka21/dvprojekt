#pragma once
#include "ILBuilding.h"

class LPowerLine :
	public ILBuilding
{
public:
	LPowerLine(const int costs, LPlayingField* lPlayingField, const int x, const int y);
	~LPowerLine();
};

