#pragma once
#include <memory>
#include "LGeneral.h"

NAMESPACE_LOGIC_B

class LPlayingField;

class IVPlayingField
{
protected:
	LPlayingField* lPlayingField;

public:
	IVPlayingField(LPlayingField* lPlayingField)
		: lPlayingField(lPlayingField)
	{}
	virtual ~IVPlayingField()
	{}

	virtual void initPlayingField() = 0;

	virtual void objectRemoved(const int x, const int y) = 0;
};

NAMESPACE_LOGIC_E