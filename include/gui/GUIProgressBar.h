#pragma once

#include "gui/objects.h"

class GUIProgressBar : public GUIObject, public RenderObject, public ActionObject
{
public:
	GUIProgressBar(rapidxml::xml_node<>* node);

public:
	// Render - Render the full object to the GL surface
	//  Return 0 on success, <0 on error
	virtual int Render(void);

	// Update - Update any UI component animations (called <= 30 FPS)
	//  Return 0 if nothing to update, 1 on success and contiue, >1 if full render required, and <0 on error
	virtual int Update(void);

	// NotifyVarChange - Notify of a variable change
	//  Returns 0 on success, <0 on error
	virtual int NotifyVarChange(const std::string& varName, const std::string& value);

protected:
	ImageResource* mEmptyBar;
	ImageResource* mFullBar;
	std::string mMinValVar;
	std::string mMaxValVar;
	std::string mCurValVar;
	float mSlide;
	float mSlideInc;
	int mSlideFrames;
	int mLastPos;

protected:
	virtual int RenderInternal(void);	   // Does the actual render
};

