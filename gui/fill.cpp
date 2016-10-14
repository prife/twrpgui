// fill.cpp - GUIFill object
#include "gui/GUIFill.h"

GUIFill::GUIFill(rapidxml::xml_node<>* node) : GUIObject(node)
{
	bool has_color = false;
	mColor = LoadAttrColor(node, "color", &has_color);
	if (!has_color) {
		LOGERR("No color specified for fill\n");
		return;
	}

	// Load the placement
	LoadPlacement(FindNode(node, "placement"), &mRenderX, &mRenderY, &mRenderW, &mRenderH);

	return;
}

int GUIFill::Render(void)
{
	if(!isConditionTrue())
		return 0;

	gr_color(mColor.red, mColor.green, mColor.blue, mColor.alpha);
	gr_fill(mRenderX, mRenderY, mRenderW, mRenderH);
	return 0;
}

