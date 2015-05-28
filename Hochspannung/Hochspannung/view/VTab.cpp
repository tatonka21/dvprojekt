#include "VTab.h"
#include "VGroup.h"
#include "VDialog.h"
#include "VMaterialLoader.h"
#include "VRegister.h"
#include "VGUIArea.h"

NAMESPACE_VIEW_B

VTab::VTab(CViewport* viewport, CFloatRect rect, const float layer)
	{
		m_viewport = viewport;
		m_zfRect = rect;
		m_fLayer = layer;
	}

VTab::VTab(CViewport* viewport, CFloatRect floatRect, CMaterial* materialBackground, const float layer)
	{
		m_fLayer = layer;
		m_viewport = viewport;
		m_zfRect = floatRect;
		m_background = new COverlay();
		m_background->SetLayer(m_fLayer);
		m_background->Init(materialBackground, m_zfRect);
		m_viewport->AddOverlay(m_background);
		m_hasBackground = true;

		
	}


	VTab::~VTab()
	{
	}

	void VTab::onNotify(const Event& events)
	{
		switch (events)
		{
		default:
			notify(events);
		}
	}

	void VTab::addContainer(const ContainerType& containerType, CFloatRect& floatRect, CMaterial* MaterialNormal, const std::basic_string<char>& sName, const float layer)
	{
		switch (containerType)
		{
		case Group:
			m_Guicontainer[sName] = new VGroup(m_viewport, createRelativeRectangle(&m_zfRect, &floatRect), MaterialNormal);
			m_Guicontainer[sName]->addObserver(this);
			break;
		case Dialog:
			m_Guicontainer[sName] = new VDialog(m_viewport, createRelativeRectangle(&m_zfRect, &floatRect), MaterialNormal, layer);
			m_Guicontainer[sName]->addObserver(this);
			break;
		case Register:
			m_Guicontainer[sName] = new VRegister(createRelativeRectangle(&m_zfRect, &floatRect), m_viewport, MaterialNormal, layer);
			m_Guicontainer[sName]->addObserver(this);
			break;
		case GUIArea:
			m_Guicontainer[sName] = new VGUIArea(m_viewport, createRelativeRectangle(&m_zfRect, &floatRect), MaterialNormal, layer);
			m_Guicontainer[sName]->addObserver(this);
			break;
		default: break;
		}
	}

	void VTab::addContainer(const ContainerType& containerType, CFloatRect& floatRect, const std::basic_string<char>& sName, const float layer)
	{
		switch (containerType)
		{
		case Group:
			m_Guicontainer[sName] = new VGroup(m_viewport, createRelativeRectangle(&m_zfRect, &floatRect));
			m_Guicontainer[sName]->addObserver(this);
			break;
		case Dialog:
			m_Guicontainer[sName] = new VDialog(m_viewport, createRelativeRectangle(&m_zfRect, &floatRect), layer);
			m_Guicontainer[sName]->addObserver(this);
			break;
		case Register:
			m_Guicontainer[sName] = new VRegister(createRelativeRectangle(&m_zfRect, &floatRect), m_viewport, layer);
			m_Guicontainer[sName]->addObserver(this);
			break;
		case GUIArea:
			m_Guicontainer[sName] = new VGUIArea(m_viewport, createRelativeRectangle(&m_zfRect, &floatRect), layer);
			m_Guicontainer[sName]->addObserver(this);
			break;
		default: break;
		}
	}

	NAMESPACE_VIEW_E
