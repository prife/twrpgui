#pragma once

#include "gui/objects.h"

// GUIAnimation - Used for animations
class GUIAnimation : public GUIObject, public RenderObject
{
public:
	GUIAnimation(rapidxml::xml_node<>* node);

public:
	// Render - Render the full object to the GL surface
	//  Return 0 on success, <0 on error
	virtual int Render(void);

	// Update - Update any UI component animations (called <= 30 FPS)
	//  Return 0 if nothing to update, 1 on success and contiue, >1 if full render required, and <0 on error
	virtual int Update(void);

protected:
	AnimationResource* mAnimation;
	int mFrame;
	int mFPS;
	int mLoop;
	int mRender;
	int mUpdateCount;
};


