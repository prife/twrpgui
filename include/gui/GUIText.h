#pragma once

#include "gui/objects.h"

// GUIText - Used for static text
class GUIText : public GUIObject, public RenderObject, public ActionObject
{
public:
	// w and h may be ignored, in which case, no bounding box is applied
	GUIText(rapidxml::xml_node<>* node);

public:
	// Render - Render the full object to the GL surface
	//  Return 0 on success, <0 on error
	virtual int Render(void);

	// Update - Update any UI component animations (called <= 30 FPS)
	//  Return 0 if nothing to update, 1 on success and contiue, >1 if full render required, and <0 on error
	virtual int Update(void);

	// Retrieve the size of the current string (dynamic strings may change per call)
	virtual int GetCurrentBounds(int& w, int& h);

	// Notify of a variable change
	virtual int NotifyVarChange(const std::string& varName, const std::string& value);

	// Set maximum width in pixels
	virtual int SetMaxWidth(unsigned width);

	void SetText(std::string newtext);

public:
	bool isHighlighted;
	bool scaleWidth;
	unsigned maxWidth;

protected:
	std::string mText;
	std::string mLastValue;
	COLOR mColor;
	COLOR mHighlightColor;
	FontResource* mFont;
	int mIsStatic;
	int mVarChanged;
	int mFontHeight;
};

