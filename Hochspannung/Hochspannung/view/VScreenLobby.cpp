#include "VScreenLobby.h"

NAMESPACE_VIEW_B
VScreenLobby::VScreenLobby()
{
}

VScreenLobby::VScreenLobby(CFrame* frame)
{
	m_viewport = new CViewport();
	m_camera.Init();
	m_viewport->InitFull(&m_camera);
	frame->AddViewport(m_viewport);


	m_background = new CBackground();

	m_background->InitFull("textures\\MainMenueBackground.png");

	m_viewport->AddBackground(m_background);

	addContainer(m_viewport,IViewGUIContainer::ContainerType::Group, CFloatRect(0, 0.7F, 1.0F, 0.3F), "Menue");
	getContainer("Menue")->addButton(CFloatRect(0.65, 0.83, 0.30, 0.12), &VMaterialLoader::materialButtonBack, &VMaterialLoader::materialButtonBackHover, IViewUIObserver::SWITCH_TO_SPIELMODUS);
	getContainer("Menue")->addButton(CFloatRect(0.65, 0.05, 0.30, 0.12), &VMaterialLoader::materialButtonMainMenueNeuesSpiel, &VMaterialLoader::materialButtonMainMenueNeuesSpielHover, IViewUIObserver::START_GAME);
	getContainer("Menue")->addButton(CFloatRect(0.65, 0.19, 0.30, 0.12), &VMaterialLoader::materialButtonMainMenueCredits, &VMaterialLoader::materialButtonMainMenueCreditsHover, IViewUIObserver::NOTHING);
	getContainer("Menue")->addTextfield(CFloatRect(0.25, 0.5, 0.30, 0.08), &VMaterialLoader::materialIngameBorder, &VMaterialLoader::materialRed, &VMaterialLoader::materialGreen,30,"Suche IP-Adresse...");

}

VScreenLobby::~VScreenLobby()
{
	for (m_IterGuicontainer = m_Guicontainer.begin(); m_IterGuicontainer != m_Guicontainer.end(); ++m_IterGuicontainer)
	{
		delete m_IterGuicontainer->second;
	}
	m_Guicontainer.clear();

	delete m_viewport;

	}
void VScreenLobby::onNotify(Event events)
{
	switch (events)
	{

	default:
		notify(events);
		break;
	}
}
void VScreenLobby::checkShortcut(CDeviceKeyboard* keyboard)
{
	if (keyboard->KeyPressed(DIK_ESCAPE))
	{
		notify(SWITCH_TO_SPIELMODUS);
	}
	if (keyboard->KeyPressed(DIK_K))
	{
		
	}

}
NAMESPACE_VIEW_E