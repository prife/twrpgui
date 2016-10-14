#pragma once

#include "gui/objects.h"

// GUIFill - Used for fill colors
class GUIFill : public GUIObject, public RenderObject
{
public:
	GUIFill(rapidxml::xml_node<>* node);

public:
	// Render - Render the full object to the GL surface
	//  Return 0 on success, <0 on error
	virtual int Render(void);

protected:
	COLOR mColor;
};


