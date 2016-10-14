#pragma once

#include "gui/GUIScrollList.h"

class GUIAction;
class GUIListBox : public GUIScrollList
{
public:
	GUIListBox(rapidxml::xml_node<>* node);
	virtual ~GUIListBox();

public:
	// Update - Update any UI component animations (called <= 30 FPS)
	//  Return 0 if nothing to update, 1 on success and contiue, >1 if full render required, and <0 on error
	virtual int Update(void);

	// NotifyVarChange - Notify of a variable change
	virtual int NotifyVarChange(const std::string& varName, const std::string& value);

	// SetPageFocus - Notify when a page gains or loses focus
	virtual void SetPageFocus(int inFocus);

	virtual size_t GetItemCount();
	virtual void RenderItem(size_t itemindex, int yPos, bool selected);
	virtual void NotifySelect(size_t item_selected);

protected:
	struct ListItem {
		std::string displayName;
		std::string variableName;
		std::string variableValue;
		unsigned int selected;
		GUIAction* action;
		std::vector<Condition> mConditions;
	};

protected:
	std::vector<ListItem> mListItems;
	std::vector<size_t> mVisibleItems; // contains indexes in mListItems of visible items only
	std::string mVariable;
	std::string currentValue;
	ImageResource* mIconSelected;
	ImageResource* mIconUnselected;
	bool isCheckList;
	bool isTextParsed;
};

