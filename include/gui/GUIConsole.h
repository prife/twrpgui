#pragma once

#include "gui/GUIScrollList.h"

class GUIConsole : public GUIScrollList
{
public:
	GUIConsole(rapidxml::xml_node<>* node);

public:
	// Render - Render the full object to the GL surface
	//  Return 0 on success, <0 on error
	virtual int Render(void);

	// Update - Update any UI component animations (called <= 30 FPS)
	//  Return 0 if nothing to update, 1 on success and contiue, >1 if full render required, and <0 on error
	virtual int Update(void);

	// IsInRegion - Checks if the request is handled by this object
	//  Return 1 if this object handles the request, 0 if not
	virtual int IsInRegion(int x, int y);

	// NotifyTouch - Notify of a touch event
	//  Return 0 on success, >0 to ignore remainder of touch, and <0 on error (Return error to allow other handlers)
	virtual int NotifyTouch(TOUCH_STATE state, int x, int y);

	// ScrollList interface
	virtual size_t GetItemCount();
	virtual void RenderItem(size_t itemindex, int yPos, bool selected);
	virtual void NotifySelect(size_t item_selected);
	static void Translate_Now();
protected:
	enum SlideoutState
	{
		hidden = 0,
		visible,
		request_hide,
		request_show
	};

	ImageResource* mSlideoutImage;
	size_t mLastCount; // lines from gConsole that are already split and copied into rConsole
	bool scrollToEnd; // true if we want to keep tracking the last line
	int mSlideoutX, mSlideoutY, mSlideoutW, mSlideoutH;
	int mSlideout;
	SlideoutState mSlideoutState;
	std::vector<std::string> rConsole;
	std::vector<std::string> rConsoleColor;

protected:
	int RenderSlideout(void);
	int RenderConsole(void);
};

