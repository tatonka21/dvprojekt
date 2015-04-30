#pragma once
#include "LGeneral.h"

NAMESPACE_LOGIC_B


class LMaster;

class LPlayer
{
public:
	enum PlayerId
	{
		Local = 0,
		External = 1
	};

private:
	int money = 5700;
	LMaster* lMaster;

public:
	LPlayer(LMaster* lMaster);
	~LPlayer();
	int getMoney() const;
	void addMoney(const int amount);
	void subtractMoney(const int amount);
};


NAMESPACE_LOGIC_E
