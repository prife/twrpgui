#pragma once

#include "gui/objects.h"

class GUIText;
class GUIAction;
// GUIInput - Used for keyboard input
class GUIInput : public GUIObject, public RenderObject, public ActionObject, public InputObject
{
public:
	GUIInput(rapidxml::xml_node<>* node);
	virtual ~GUIInput();

public:
	// Render - Render the full object to the GL surface
	//  Return 0 on success, <0 on error
	virtual int Render(void);

	// Update - Update any UI component animations (called <= 30 FPS)
	//  Return 0 if nothing to update, 1 on success and contiue, >1 if full render required, and <0 on error
	virtual int Update(void);

	// Notify of a variable change
	virtual int NotifyVarChange(const std::string& varName, const std::string& value);

	// NotifyTouch - Notify of a touch event
	//  Return 0 on success, >0 to ignore remainder of touch, and <0 on error
	virtual int NotifyTouch(TOUCH_STATE state, int x, int y);

	virtual int NotifyKey(int key, bool down);
	virtual int NotifyCharInput(int ch);

protected:
	virtual int GetSelection(int x, int y);

	// Handles displaying the text properly when chars are added, deleted, or for scrolling
	void HandleTextLocation(int x);
	void UpdateTextWidth();
	void HandleCursorByTouch(int x);
	void HandleCursorByText();

protected:
	GUIText* mInputText;
	GUIAction* mAction;
	ImageResource* mBackground;
	ImageResource* mCursor;
	FontResource* mFont;
	std::string mText;
	std::string mLastValue;
	std::string mVariable;
	std::string mMask;
	std::string displayValue;
	COLOR mBackgroundColor;
	COLOR mCursorColor;
	int scrollingX;
	int cursorX;
	int lastX;
	int mCursorLocation;
	int mBackgroundX, mBackgroundY, mBackgroundW, mBackgroundH;
	int mFontY;
	int textWidth;
	unsigned mFontHeight;
	unsigned CursorWidth;
	bool mRendered;
	bool HasMask;
	bool DrawCursor;
	bool isLocalChange;
	bool HasAllowed;
	bool HasDisabled;
	std::string AllowedList;
	std::string DisabledList;
	unsigned MinLen;
	unsigned MaxLen;
};

