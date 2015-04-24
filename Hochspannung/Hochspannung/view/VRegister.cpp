#include "VRegister.h"
#include "VGroup.h"
#include "VDialog.h"
#include "VMaterialLoader.h"

NAMESPACE_VIEW_B
VRegister::VRegister()
{
}

VRegister::VRegister(CFloatRect floatRect, CViewport* viewport)
{
		m_viewport = viewport;
		m_zfRect = floatRect;
		m_background = new COverlay();
		m_background->SetLayer(0.9);
		m_background->Init(&VMaterialLoader::materialBlue,m_zfRect);
		//float breiteButton = floatRect.GetXSize() / anzahlRegisterkarten;
		m_viewport->AddOverlay(m_background);

}

VRegister::~VRegister()
{
	for (lIterGUIObjects = m_guiObjects.begin(); lIterGUIObjects != m_guiObjects.end(); ++lIterGUIObjects)
	{
		delete lIterGUIObjects->second;
	}
	m_guiObjects.clear();
}

	void VRegister::addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, Event clickAction, string sName)
	{
		m_guiObjects[sName] = new VButton(m_viewport, createRelativeRectangle(&m_zfRect, &rect), MaterialNormal, MaterialHover, clickAction);

		m_guiObjects[sName]->addObserver(this);

	
	}

	void VRegister::addTextfield(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, const int& MaxChars, const string& Placeholder, string sName)
	{
		m_guiObjects[sName] = new VTextfield(m_viewport, createRelativeRectangle(&m_zfRect, &rect), MaterialNormal, MaterialHover, MaterialActive, MaxChars, Placeholder);

		m_guiObjects[sName]->addObserver(this);

	
	}

	void VRegister::addText(CFloatRect rect, CWritingFont* writingFont, string text, string sName)
	{
		m_guiObjects[sName] = new VText(m_viewport, createRelativeRectangle(&m_zfRect, &rect), writingFont, text);

		m_guiObjects[sName]->addObserver(this);

	}

	void VRegister::onNotify(Event events)
	{
		switch (events)
		{
		/*case SWITCH_TO_REGISTER_BUILDING:
		{
			
		}
		break;
		case SWITCH_TO_REGISTER_SABOTAGE:
		{

		}
		break;
		case SWITCH_TO_REGISTER_STATISTICS:
		{

		}
		break;*/
		default:
				notify(events);
				break;
		}
	}

	void VRegister::addContainer(const IViewGUIContainer::ContainerType& containerType, const CFloatRect& floatRect, const string& sName)
	{
		switch (containerType)
		{
		case Group:
			m_Guicontainer[sName] = new VGroup(m_viewport, floatRect);
			m_Guicontainer[sName]->addObserver(this);
			break;
		case Dialog:
			m_Guicontainer[sName] = new VDialog(m_viewport, floatRect, &VMaterialLoader::materialDialogBackground);
			m_Guicontainer[sName]->addObserver(this);
			break;
		}
	}


	void VRegister::switchOn()
	{
		for (lIterGUIObjects = m_guiObjects.begin(); lIterGUIObjects != m_guiObjects.end(); ++lIterGUIObjects)
		{
			lIterGUIObjects->second->switchOn();

		}
		m_background->SwitchOn();

		m_bOn = true;
	}


	void VRegister::switchOff()
	{
		for (lIterGUIObjects = m_guiObjects.begin(); lIterGUIObjects != m_guiObjects.end(); ++lIterGUIObjects)
		{
			
			lIterGUIObjects->second->switchOff();

		}
		m_background->SwitchOff();
		m_bOn = false;
	}

	void VRegister::addTab(CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* background, Event events, string sName)
{
	m_Guicontainer[sName] = new VTab(m_viewport, createRelativeRectangle(&m_zfRect, &CFloatRect(0.0,0.2,1,0.8)), background);
	m_tabs[sName] = dynamic_cast<VTab*>(m_Guicontainer[sName]);
	m_Guicontainer[sName]->addObserver(this);

	//addButton(createRelativeRectangle(&m_zfRect, &CFloatRect(0, 0.0, 0.5, 0.1)), MaterialNormal, MaterialHover, events, sName);
	addButton(CFloatRect(0, 0.0, 0.5, 0.1), MaterialNormal, MaterialHover, events, sName);

	calcButtonSize();
}

	void VRegister::calcButtonSize()
	{
		int i=0;
		for (lIterGUIObjects = m_guiObjects.begin(); lIterGUIObjects != m_guiObjects.end(); ++lIterGUIObjects)
		{
			//GUI Object Size Mehode hinzufügen
			CFloatRect tempRect=lIterGUIObjects->second->getRectangle();
			lIterGUIObjects->second->setRectangle(createRelativeRectangle(&m_zfRect, &CFloatRect(1 / static_cast<float>(m_guiObjects.size())*static_cast<float>(i), 0.0, 1 / static_cast<float>(m_guiObjects.size()), 0.2)));
			lIterGUIObjects->second->updateRectangle(createRelativeRectangle(&m_zfRect, &CFloatRect(1 / static_cast<float>(m_guiObjects.size())*static_cast<float>(i), 0.0, 1 / static_cast<float>(m_guiObjects.size()), 0.2)));
			lIterGUIObjects->second->setLayer(0.3);
				i++;
		}
	}

	void VRegister::SwitchToTab(string sName)
	{
		
		map<string, VTab*>::iterator it = m_tabs.find(sName);
		ASSERT(it != m_tabs.end(), "Tab not available");

		for (it = m_tabs.begin(); it != m_tabs.end(); it++)
		{
			it->second->switchOff();
		}

		m_tabs[sName]->switchOn();
	}

	VTab* VRegister::getTab(string sName)
	{
		map<string, VTab*>::iterator it = m_tabs.find(sName);
		ASSERT(it != m_tabs.end(), "Tab not available");
		return m_tabs[sName];
	}

	NAMESPACE_VIEW_E