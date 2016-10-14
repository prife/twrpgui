#pragma once

#include "gui/objects.h"

class GUIAction;
class GUIText;
class GUISlider : public GUIObject, public RenderObject, public ActionObject
{
public:
	GUISlider(rapidxml::xml_node<>* node);
	virtual ~GUISlider();

public:
	// Render - Render the full object to the GL surface
	//  Return 0 on success, <0 on error
	virtual int Render(void);

	// Update - Update any UI component animations (called <= 30 FPS)
	//  Return 0 if nothing to update, 1 on success and contiue, >1 if full render required, and <0 on error
	virtual int Update(void);

	// NotifyTouch - Notify of a touch event
	//  Return 0 on success, >0 to ignore remainder of touch, and <0 on error
	virtual int NotifyTouch(TOUCH_STATE state, int x, int y);

protected:
	GUIAction* sAction;
	GUIText* sSliderLabel;
	ImageResource* sSlider;
	ImageResource* sSliderUsed;
	ImageResource* sTouch;
	int sTouchW, sTouchH;
	int sCurTouchX;
	int sUpdate;
};

