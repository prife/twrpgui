#pragma once

#include "gui/objects.h"

class GUIText;
class GUIAction;
class GUISliderValue: public GUIObject, public RenderObject, public ActionObject
{
public:
	GUISliderValue(rapidxml::xml_node<>* node);
	virtual ~GUISliderValue();

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

	// Notify of a variable change
	virtual int NotifyVarChange(const std::string& varName, const std::string& value);

	// SetPageFocus - Notify when a page gains or loses focus
	virtual void SetPageFocus(int inFocus);

protected:
	int measureText(const std::string& str);
	int valueFromPct(float pct);
	float pctFromValue(int value);
	void loadValue(bool force = false);

	std::string mVariable;
	int mMax;
	int mMin;
	int mValue;
	char *mValueStr;
	float mValuePct;
	std::string mMaxStr;
	std::string mMinStr;
	FontResource *mFont;
	GUIText* mLabel;
	int mLabelW;
	COLOR mTextColor;
	COLOR mLineColor;
	COLOR mSliderColor;
	bool mShowRange;
	bool mShowCurr;
	int mLineX;
	int mLineY;
	int mLineH;
	int mLinePadding;
	int mPadding;
	int mSliderY;
	int mSliderW;
	int mSliderH;
	bool mRendered;
	int mFontHeight;
	GUIAction *mAction;
	bool mChangeOnDrag;
	int mLineW;
	bool mDragging;
	ImageResource *mBackgroundImage;
	ImageResource *mHandleImage;
	ImageResource *mHandleHoverImage;
};


