#pragma once

#include "gui/GUIScrollList.h"

class GUIPartitionList : public GUIScrollList
{
public:
	GUIPartitionList(rapidxml::xml_node<>* node);
	virtual ~GUIPartitionList();

public:
	// Update - Update any UI component animations (called <= 30 FPS)
	//  Return 0 if nothing to update, 1 on success and contiue, >1 if full render required, and <0 on error
	virtual int Update();

	// NotifyVarChange - Notify of a variable change
	virtual int NotifyVarChange(const std::string& varName, const std::string& value);

	// SetPageFocus - Notify when a page gains or loses focus
	virtual void SetPageFocus(int inFocus);

	virtual size_t GetItemCount();
	virtual void RenderItem(size_t itemindex, int yPos, bool selected);
	virtual void NotifySelect(size_t item_selected);

protected:
	void MatchList();
	void SetPosition();

protected:
	std::vector<PartitionList> mList;
	std::string ListType;
	std::string mVariable;
	std::string selectedList;
	std::string currentValue;
	std::string mLastValue;
	ImageResource* mIconSelected;
	ImageResource* mIconUnselected;
	bool updateList;
};

