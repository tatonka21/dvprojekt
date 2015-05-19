#pragma once

#include <string>
#include <vector>

namespace Network {

enum Action {
	UNDEFINED,

	SET_OBJECT,
	DELETE_OBJECT,
	UPGRADE_OBJECT,

	START_GAME,
	END_GAME,
	PAUSE_GAME,
	CONTINUE_GAME,

	SET_MAPSIZE,
	SET_MAPROW,

	CHECK_CONNECTION,
	CHECK_RESPONSE,

	SEND_SABOTAGE,
	SEND_SWITCH_STATE,

	SEND_STATISTIC
};

struct FieldTransfer {
	int iObjectID = -99;
	int iPlayerID = -99;
	int iFieldLevel = -99;
	int iFieldType = -99;
};

class CTransferObject {
public:

	CTransferObject(Action action = UNDEFINED, int iTransObjectID = -1, int iCoordX = -1, int iCoordY = -1, std::string sValue = "");
	~CTransferObject();

	Action getAction();
	void setAction(Action action);

	int getTransObjectID();
	void setTransObjectID(int iTransObjectID);
	
	int getCoordX();
	void setCoordX(int iCoordX);

	int getCoordY();
	void setCoordY(int iCoordY);

	std::string getValue();
	void setValue(std::string sValue);

	/**
	 * @brief A get function for the m_sValue member of TransferObject.
	 * @return std::vector<FieldTransfer>
	 */
	std::vector<FieldTransfer> getValueAsVector();

private:
	Action m_Action;
	int m_iTransObjectID;
	int m_iCoordX;
	int m_iCoordY;
	std::string m_sValue;
	// to be continued...

};

}