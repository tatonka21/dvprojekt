#include "VScreenOptions.h"
#include "VUI.h"
#include "VGraph.h"

NAMESPACE_VIEW_B


	VScreenOptions::VScreenOptions(VUI* vUi) : IViewScreen(vUi)
	{
		m_viewport = new CViewport();
		m_camera.Init();
		m_viewport->InitFull(&m_camera);
		vUi->m_zf.AddViewport(m_viewport);

		//Cursor
		switchCursor("textures/gui/default_zeiger.png", true);

		m_background = new CBackground();

		m_background->InitFull(&VMaterialLoader::materialDefaultBackground);

		m_viewport->AddBackground(m_background);

		addContainer(m_viewport, IViewGUIContainer::ContainerType::Group, CFloatRect(0.0F, 0.7F, 1.0F, 0.3F), "Menue");
		getContainer("Menue")->addButton(CFloatRect(0.65F, 0.83F, 0.30F, 0.12F), &VMaterialLoader::materialButtonBack, &VMaterialLoader::materialButtonBackHover, SWITCH_TO_MAINMENUE, "buttonBackMainMenue");
	}

	VScreenOptions::~VScreenOptions()
	{
		
	}

	void VScreenOptions::onNotify(const Event& events)
	{
		switch (events)
		{
		default:
			notify(events);
			break;
		}
	}

	void VScreenOptions::checkShortcut(CDeviceKeyboard* keyboard)
	{
		if (keyboard->KeyPressed(DIK_ESCAPE))
		{
			notify(SWITCH_TO_MAINMENUE);
		}
	}

	void VScreenOptions::checkSpecialEvent(CDeviceCursor* cursor)
	{
	}


	void VScreenOptions::tick(const float fTimeDelta)
	{
		updateCursorImagePos(&vUi->m_zkCursor);

		if (!vUi->m_zkCursor.ButtonPressedLeft())
		{
			vUi->m_BlockCursorLeftPressed = false;
		}

		std::unordered_map<std::string, IViewGUIContainer*> tempGuiContainer;

		checkShortcut(&vUi->m_zkKeyboard);
		checkSpecialEvent(&vUi->m_zkCursor);
		tempGuiContainer = getGuiContainerMap();

		//For all containers in the screen
		for (const std::pair<std::string, IViewGUIContainer*>& ContainerPair : tempGuiContainer)
		{
			checkGUIContainer(ContainerPair.second);
		}

		if (vUi->m_zkCursor.ButtonPressedLeft())
		{
			vUi->m_BlockCursorLeftPressed = true;
		}
	}

	void VScreenOptions::checkGUIObjects(IViewGUIContainer* tempGuicontainer)
	{
		std::unordered_map<std::string, IViewGUIObject*> tempGUIObjects = tempGuicontainer->getGuiObjectList();

		for (const std::pair<std::string, IViewGUIObject*>& ObjectPair : tempGUIObjects)
		{
			if (ObjectPair.second->isOn())
			{
				if (!vUi->m_BlockCursorLeftPressed)
				{
					//check for events
					ObjectPair.second->checkEvent(&vUi->m_zkCursor, &vUi->m_zkKeyboard);
				}
				//if screen was changed
				if (vUi->m_screenChanged)
				{
					vUi->m_screenChanged = false;

					vUi->m_BlockCursorLeftPressed = true;
					return;
				}
			}
		}
	}


	void VScreenOptions::checkGUIContainer(IViewGUIContainer* tempGuicontainer)
	{
		std::unordered_map<std::string, IViewGUIContainer*> tempGuiContainerMap;

		tempGuiContainerMap = tempGuicontainer->getGuiContainerMap();

		checkGUIObjects(tempGuicontainer);
		for (const std::pair<std::string, IViewGUIContainer*>& ContainerPair : tempGuiContainerMap)
		{
			checkGUIObjects(ContainerPair.second);

			if (tempGuicontainer->getGuiContainerMap().size() > 0)
			{
				checkGUIContainer(ContainerPair.second);
			}
		}
	}

	void VScreenOptions::startAnimation()
	{
	}

	void VScreenOptions::StartEvent()
	{
	}

	void VScreenOptions::EndEvent()
	{
	}

	void VScreenOptions::resize(const int width, const int height)
	{
	}

	NAMESPACE_VIEW_E
