#pragma once

#include "gui/GUIScrollList.h"

class GUITextBox : public GUIScrollList
{
public:
	GUITextBox(rapidxml::xml_node<>* node);

public:
	// Update - Update any UI component animations (called <= 30 FPS)
	//  Return 0 if nothing to update, 1 on success and contiue, >1 if full render required, and <0 on error
	virtual int Update(void);

	// NotifyVarChange - Notify of a variable change
	virtual int NotifyVarChange(const std::string& varName, const std::string& value);

	// ScrollList interface
	virtual size_t GetItemCount();
	virtual void RenderItem(size_t itemindex, int yPos, bool selected);
	virtual void NotifySelect(size_t item_selected);
protected:

	size_t mLastCount;
	bool mIsStatic;
	std::vector<std::string> mLastValue; // Parsed text - parsed for variables but not word wrapped
	std::vector<std::string> mText;      // Original text - not parsed for variables and not word wrapped
	std::vector<std::string> rText;      // Rendered text - what we actually see

};

