#pragma once

#include "VGeneral.h"
#include "IViewUIObserver.h"
#include "IViewScreen.h"
#include "../logic/IVTickObserver.h"
#include "../logic/LPlayer.h"
#include <mutex>

NAMESPACE_VIEW_B


class VMaster;
class VScreenIngame;
class VScreenMainMenue;
class VScreenOptions;
class VScreenHelp;
class VScreenControls;
class VScreenCredits;
class VScreenLobby;

/**
 * @brief The VUI class is the base class for the UI.
 */
class VUI : public IVTickObserver, public IViewUIObserver
{
	NON_COPYABLE(VUI);
	friend class VMaster;
	friend class VScreenIngame;
	friend class VScreenMainMenue;
	friend class VScreenOptions;
	friend class VScreenHelp;
	friend class VScreenControls;
	friend class VScreenCredits;
	friend class VScreenLobby;
	friend class VScreenGameOver;
	

	enum CursorType
	{
		Default,
		Hammer,
		Sabotage,
		PowerOn,
		PowerOff,
		Sell
	};

private:
	VMaster* vMaster;

	CRoot m_zr;
	CFrame m_zf;
	CDeviceKeyboard m_zkKeyboard;
	CDeviceCursor m_zkCursor;
	CDeviceMouse m_zkMouse;

	IViewScreen* activeScreen = nullptr;
	std::unordered_map<std::string, IViewScreen*> m_screens;

	bool isQuit;
	bool m_screenChanged = false;
	bool m_BlockCursorLeftPressed = false;

	HWND m_hwnd = nullptr;

	HCURSOR m_Default_Cursor;
	HCURSOR m_Hammer_Cursor;
	HCURSOR m_Sabotage_Cursor;
	HCURSOR m_PowerOn_Cursor;
	HCURSOR m_PowerOff_Cursor;
	HCURSOR m_Sell_Cursor;

	std::mutex mutex;
public:
	explicit VUI(VMaster* vMaster);
	virtual ~VUI() override;

	virtual void tick(const float fTimeDelta) override;

	virtual void onNotify(const Event& events) override;

	void addScreen(const std::string& sName, const IViewScreen::ScreenType);
	void switchScreen(const std::string& switchTo);
	IViewScreen* getScreen(const std::string& sName);

	void initUI(HWND hwnd, CSplash* psplash);

	void resize(int width, int height);
	void updateMoney(const int wert, const LPlayer::PlayerId playerId);
	void updatePopulation(const int wert);
	void updateAddedPowerPlant(const LIdentifier::LIdentifier id, const LPlayer::PlayerId playerId);
	void updateRemovedPowerPlant(const LIdentifier::LIdentifier id, const LPlayer::PlayerId playerId);
	void updateNumberPowerLines(const int newNumberPowerLines, const LPlayer::PlayerId playerId);
	void updateEnergySurplus(const int surplusRatio);
	void updateGameList(const std::unordered_map<std::string, Network::CGameObject>& gameList);
	void updateRegenerativeRatioLocal(float ratio);
	void updateRegenerativeRatioRemote(float ratio);
	void switchCursor(const CursorType& cursorType);
	void showMessage(const std::string& message);
	void removeMaterialFromRoot(CMaterial* material);
	void setSabotageNumber(const int value);
	
	//Sell value

	void contextMenuUpdateValue(const std::pair<int, int> & pos, const int value);
	void contextMenuUpdateResourceValue(const std::pair<int, int> & pos, const int resourceValue);
	void contextMenuUpdatePopulation(const std::pair<int, int> & pos, const int population);
	void contextMenuUpdateEnergy(const std::pair<int, int> & pos, const int energy);
	void contextMenuUpdateEnergySurplus(const std::pair<int, int> & pos, const int surplus);

	void sabotageCostChanged(const int cost, const LSabotage::LSabotage sabotage);

	void gameOver(bool win);
};


NAMESPACE_VIEW_E
