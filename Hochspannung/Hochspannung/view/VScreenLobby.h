#pragma once
#include "IViewScreen.h"
NAMESPACE_VIEW_B
class VScreenLobby :
	public IViewScreen
{
public:
	VScreenLobby();
	VScreenLobby(CFrame* frame);
	~VScreenLobby();
	void onNotify(Event events)override;
	void checkShortcut(CDeviceKeyboard* keyboard) override;

private:
	CBackground* m_background;

};

NAMESPACE_VIEW_E