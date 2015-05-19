#include "VListView.h"
#include "VGroup.h"
#include "VDialog.h"
#include "VRegister.h"
#include "VGUIArea.h"
#include "VMaterialLoader.h"
NAMESPACE_VIEW_B



VListView::VListView()
{
}

VListView::VListView(CFloatRect floatRect, CViewport* viewport)
	{
		m_viewport = viewport;
		m_zfRect = floatRect;
	}

	VListView::VListView(CFloatRect floatRect, CViewport* viewport, CMaterial* materialBackground)
	{
		m_viewport = viewport;
		m_zfRect = floatRect;
		m_background = new COverlay();
		m_background->SetLayer(0.2F);
		m_background->Init(materialBackground, m_zfRect);
		m_viewport->AddOverlay(m_background);
		m_hasBackground = true;
	}

	void VListView::onNotify(const Event& evente)
	{
		switch (evente)
		{
		default:
			notify(evente);
			break;
		}
	}

	void VListView::addContainer(const ContainerType& containerType, CFloatRect& floatRect, const std::string& sName)
	{
		switch (containerType)
		{
		case Group:
			m_Guicontainer[sName] = new VGroup(m_viewport, createRelativeRectangle(&m_zfRect, &floatRect));
			m_Guicontainer[sName]->addObserver(this);
			break;
		case Dialog:
			m_Guicontainer[sName] = new VDialog(m_viewport, createRelativeRectangle(&m_zfRect, &floatRect));
			m_Guicontainer[sName]->addObserver(this);
			break;
		case Register:
			m_Guicontainer[sName] = new VRegister(createRelativeRectangle(&m_zfRect, &floatRect), m_viewport);
			m_Guicontainer[sName]->addObserver(this);
			break;
		case GUIArea:
			m_Guicontainer[sName] = new VGUIArea(m_viewport, createRelativeRectangle(&m_zfRect, &floatRect));
			m_Guicontainer[sName]->addObserver(this);
			break;
		default: break;
		}
		
	}

	void VListView::addContainer(const ContainerType& containerType, CFloatRect& floatRect, CMaterial* MaterialNormal, const std::string& sName)
	{
		switch (containerType)
		{
		case Group:
			m_Guicontainer[sName] = new VGroup(m_viewport, createRelativeRectangle(&m_zfRect, &floatRect), MaterialNormal);
			m_Guicontainer[sName]->addObserver(this);
			break;
		case Dialog:
			m_Guicontainer[sName] = new VDialog(m_viewport, createRelativeRectangle(&m_zfRect, &floatRect), MaterialNormal);
			m_Guicontainer[sName]->addObserver(this);
			break;
		case Register:
			m_Guicontainer[sName] = new VRegister(createRelativeRectangle(&m_zfRect, &floatRect), m_viewport, MaterialNormal);
			m_Guicontainer[sName]->addObserver(this);
			break;
		case GUIArea:
			m_Guicontainer[sName] = new VGUIArea(m_viewport, createRelativeRectangle(&m_zfRect, &floatRect), MaterialNormal);
			m_Guicontainer[sName]->addObserver(this);
			break;
		default: break;
		}
	}


VButton* VListView::addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, Event clickAction, std::string sName)
{
	m_guiObjects[sName] = new VButton(m_viewport, createRelativeRectangle(&m_zfRect, &rect), MaterialNormal, MaterialHover, clickAction);

	m_guiObjects[sName]->addObserver(this);
	return CASTD<VButton*>(m_guiObjects[sName]);
}

VTextfield* VListView::addTextfield(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, CMaterial* MaterialActive, const int& MaxChars, const std::string& Placeholder, std::string sName)
{
	m_guiObjects[sName] = new VListEntry(m_viewport, &VMaterialLoader::materialGreen, &VMaterialLoader::materialRed, sName);

	m_guiObjects[sName]->addObserver(this);
	return CASTD<VTextfield*>(m_guiObjects[sName]);
}

VText* VListView::addText(CFloatRect rect, CWritingFont* writingFont, std::string text, std::string sName)
{
	for (const std::string& key : m_entries)
	{
		delete m_guiObjects[key];
		m_guiObjects.erase(key);

	m_guiObjects[sName]->addObserver(this);
	return CASTD<VText*>(m_guiObjects[sName]);
}
	m_entries.clear();

COverlay* VListView::addOverlay(CFloatRect rect, CMaterial* MaterialNormal, const std::string &sName)
{
	m_Overlays[sName] = new COverlay();
	m_Overlays[sName]->Init(MaterialNormal, createRelativeRectangle(&m_zfRect, &rect));
	m_viewport->AddOverlay(m_Overlays[sName]);
	return m_Overlays[sName];
}

}

void VListView::addEntry(CMaterial* MaterialEntryNormal, CMaterial* MaterialEntryHover, const std::string &sName)
	{
	m_entries[sName] = new VListEntry(m_viewport, MaterialEntryNormal, MaterialEntryHover,sName);
	m_guiObjects[sName] = m_entries[sName];
		m_guiObjects[sName]->addObserverExt(this);
		calcEntrySize(); 
	}

	void VListView::updateList(const std::vector<Network::CGameObject>& hostList)
	{
		for (const std::string& key : m_entries)
		{
			delete m_guiObjects[key];
			m_guiObjects.erase(key);
			
		}
		m_entries.clear();
		
		for (const Network::CGameObject& go : hostList)
		{
			m_entries.push_back(go.getServerIP());
			addEntry(go.getServerIP());
			
		}
	}

	void VListView::onNotifyExt(const Event& evente, const std::basic_string<char>& sName)
	{
		switch (evente)
		{
		case LIST_ITEM_SELECTED:
			m_selectedItem = m_guiObjects[sName];
			break;
		}
	}

	IViewGUIObject* VListView::getSelectedItem()
	{
		return m_selectedItem;
	}

	void VListView::calcEntrySize()
	{
		int i = 0;
		for (const std::string& sName : m_entries)
		{
			//GUI Object Size Mehode hinzufügen
			m_guiObjects[sName]->setRectangle(createRelativeRectangle(&m_zfRect, &CFloatRect(0.1F, 0.1F* static_cast<float>(i)+0.1F, 0.8F, 0.08F)));
			m_guiObjects[sName]->updateRectangle(createRelativeRectangle(&m_zfRect, &CFloatRect(0.1F, 0.1F * static_cast<float>(i)+0.1F, 0.8F, 0.08F)));
			m_guiObjects[sName]->setLayer(0.1F);
			i++;
		}
	}


	VListView::~VListView()
{
	//TODO refactor
	//for (m_lIterGUIObjects = m_guiObjects.begin(); m_lIterGUIObjects != m_guiObjects.end(); ++m_lIterGUIObjects)
	//{
	//	delete m_lIterGUIObjects->second;
	//}
	//m_guiObjects.clear();
	//if (m_hasBackground) delete m_background;
}

NAMESPACE_VIEW_E
