#pragma once

#include "gui/objects.h"

// GUIImage - Used for static image
class GUIImage : public GUIObject, public RenderObject
{
public:
	GUIImage(rapidxml::xml_node<>* node);

public:
	// Render - Render the full object to the GL surface
	//  Return 0 on success, <0 on error
	virtual int Render(void);

	// SetRenderPos - Update the position of the object
	//  Return 0 on success, <0 on error
	virtual int SetRenderPos(int x, int y, int w = 0, int h = 0);

public:
	bool isHighlighted;

protected:
	ImageResource* mImage;
	ImageResource* mHighlightImage;
};

