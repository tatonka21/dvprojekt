#pragma once

#include "IViewGUIContainer.h"
#include "IViewGUIObject.h"
#include "IViewUIObserver.h"
#include "IViewSubject.h"



//---------------------------------------------------
// Klasse: CGroup
// Beschreibung:
//
// Autor: Patrick Benkowitsch
//---------------------------------------------------
NAMESPACE_VIEW_B

class VGroup:public IViewGUIContainer
{
public:
	VGroup(CFloatRect floatRect,CViewport& viewport);
	VGroup();
	~VGroup();
	void addButton(CFloatRect rect, CMaterial* MaterialNormal, CMaterial* MaterialHover, IViewUIObserver::Event clickAction);
	 void onNotify(IViewUIObserver::Event);
	 list<IViewGUIObject*> getGuiObjectList();
private:
	CFloatRect m_rect;
	CViewport* m_viewport;
	list<IViewGUIObject*> m_guiObjects;
	list<IViewGUIObject*>::iterator lIterGUIObjects;
	
	
};

NAMESPACE_VIEW_E