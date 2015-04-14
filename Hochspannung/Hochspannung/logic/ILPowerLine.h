#pragma once
#include "ILBuilding.h"

class IVPowerLine;
class LPlayingField;

class ILPowerLine : public ILBuilding
{
public:
	enum PowerLineOrientation
	{
		NORTH = 0x1,
		EAST = 0x2,
		SOUTH = 0x4,
		WEST = 0x8
	};

protected:
	PowerLineOrientation orientation;
	int energyValue;
	std::shared_ptr<IVPowerLine> vPowerLine;

public:
	ILPowerLine(const int costs, const int energyValue, PowerLineOrientation orientation, LField* lField, const std::shared_ptr<IVPowerLine>& vPowerLine)
		: ILBuilding(costs, lField),
		vPowerLine(vPowerLine),
		energyValue(energyValue),
		orientation(orientation)
	{};

	virtual ~ILPowerLine()
	{
	};

	int getEnergyValue() const
	{
		return energyValue;
	};

	PowerLineOrientation getPowerLineOrientation()
	{
		return orientation;
	};

};