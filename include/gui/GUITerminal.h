#pragma once

#include "gui/GUIScrollList.h"

class TerminalEngine;
class GUITerminal : public GUIScrollList, public InputObject
{
public:
	GUITerminal(rapidxml::xml_node<>* node);

public:
	// Update - Update any UI component animations (called <= 30 FPS)
	//  Return 0 if nothing to update, 1 on success and contiue, >1 if full render required, and <0 on error
	virtual int Update(void);

	// NotifyTouch - Notify of a touch event
	//  Return 0 on success, >0 to ignore remainder of touch, and <0 on error (Return error to allow other handlers)
	virtual int NotifyTouch(TOUCH_STATE state, int x, int y);

	// NotifyKey - Notify of a key press
	//  Return 0 on success (and consume key), >0 to pass key to next handler, and <0 on error
	virtual int NotifyKey(int key, bool down);

	// character input
	virtual int NotifyCharInput(int ch);

	// SetPageFocus - Notify when a page gains or loses focus
	virtual void SetPageFocus(int inFocus);

	// ScrollList interface
	virtual size_t GetItemCount();
	virtual void RenderItem(size_t itemindex, int yPos, bool selected);
	virtual void NotifySelect(size_t item_selected);
protected:
	void InitAndResize();

	TerminalEngine* engine; // non-visual parts of the terminal (text buffer etc.), not owned
	int updateCounter; // to track if anything changed in the back-end
	bool lastCondition; // to track if the condition became true and we might need to resize the terminal engine
};

