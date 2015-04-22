#include "VRegister.h"

NAMESPACE_VIEW_B
VRegister::VRegister()
{
}

	VRegister::VRegister(CFloatRect floatRect, CViewport* viewport, CMaterial* MaterialNormal)
	{
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
		m_guiObjects[sName] = new VButton(m_viewport, createRelativeRectangle(&m_rect, &rect), MaterialNormal, MaterialHover, clickAction);

		m_guiObjects[sName]->addObserver(this);

	
	}

	void VRegister::addTextfield(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, const int& MaxChars, const string& Placeholder, string sName)
	{
		m_guiObjects[sName] = new VTextfield(m_viewport, createRelativeRectangle(&m_rect, &rect), MaterialNormal, MaterialHover, MaterialActive, MaxChars, Placeholder);

		m_guiObjects[sName]->addObserver(this);

	
	}

	void VRegister::addText(CFloatRect rect, CWritingFont* writingFont, string text, string sName)
	{
		m_guiObjects[sName] = new VText(m_viewport, createRelativeRectangle(&m_rect, &rect), writingFont, text);

		m_guiObjects[sName]->addObserver(this);

	}

	void VRegister::onNotify(Event events)
	{
		switch (events)
		{
		default:
				notify(events);

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

	NAMESPACE_VIEW_E