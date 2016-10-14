#pragma once

#include "gui/objects.h"

class GUIImage;
class ImageResource;
class GUIText;
class GUIAction;

class GUIButton : public GUIObject, public RenderObject, public ActionObject
{
public:
	GUIButton(rapidxml::xml_node<>* node);
	virtual ~GUIButton();

public:
	// Render - Render the full object to the GL surface
	//  Return 0 on success, <0 on error
	virtual int Render(void);

	// Update - Update any UI component animations (called <= 30 FPS)
	//  Return 0 if nothing to update, 1 on success and contiue, >1 if full render required, and <0 on error
	virtual int Update(void);

	// SetPos - Update the position of the render object
	//  Return 0 on success, <0 on error
	virtual int SetRenderPos(int x, int y, int w = 0, int h = 0);

	// NotifyTouch - Notify of a touch event
	//  Return 0 on success, >0 to ignore remainder of touch, and <0 on error
	virtual int NotifyTouch(TOUCH_STATE state, int x, int y);

protected:
	GUIImage* mButtonImg;
	ImageResource* mButtonIcon;
	GUIText* mButtonLabel;
	GUIAction* mAction;
	int mTextX, mTextY, mTextW, mTextH;
	int mIconX, mIconY, mIconW, mIconH;
	bool mRendered;
	bool hasHighlightColor;
	bool renderHighlight;
	bool hasFill;
	COLOR mFillColor;
	COLOR mHighlightColor;
	Placement TextPlacement;
};


