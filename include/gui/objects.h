/*
	Copyright 2013 bigbiff/Dees_Troy TeamWin
	This file is part of TWRP/TeamWin Recovery Project.

	TWRP is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	TWRP is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with TWRP.  If not, see <http://www.gnu.org/licenses/>.
*/

// objects.h - Base classes for object manager of GUI

#ifndef _OBJECTS_HEADER
#define _OBJECTS_HEADER

#include <vector>
#include <string>
#include <set>
#include "common/twcommon.h"
#include "common/data.h"
#include "minuitwrp/minui.h"
#include "gui/rapidxml.h"
#include "gui/resources.h"
#include "gui/placement.h"

#ifndef TW_X_OFFSET
#define TW_X_OFFSET 0
#endif
#ifndef TW_Y_OFFSET
#define TW_Y_OFFSET 0
#endif

enum TOUCH_STATE {
	TOUCH_START = 0,
	TOUCH_DRAG = 1,
	TOUCH_RELEASE = 2,
	TOUCH_HOLD = 3,
	TOUCH_REPEAT = 4
};

struct COLOR {
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	unsigned char alpha;
	COLOR() : red(0), green(0), blue(0), alpha(0) {}
	COLOR(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255)
		: red(r), green(g), blue(b), alpha(a) {}
};

#include "gui/utils.h"

class RenderObject
{
public:
	RenderObject() { mRenderX = 0; mRenderY = 0; mRenderW = 0; mRenderH = 0; mPlacement = TOP_LEFT; }
	virtual ~RenderObject() {}

public:
	// Render - Render the full object to the GL surface
	//  Return 0 on success, <0 on error
	virtual int Render(void) = 0;

	// Update - Update any UI component animations (called <= 30 FPS)
	//  Return 0 if nothing to update, 1 on success and contiue, >1 if full render required, and <0 on error
	virtual int Update(void) { return 0; }

	// GetRenderPos - Returns the current position of the object
	virtual int GetRenderPos(int& x, int& y, int& w, int& h) { x = mRenderX; y = mRenderY; w = mRenderW; h = mRenderH; return 0; }

	// SetRenderPos - Update the position of the object
	//  Return 0 on success, <0 on error
	virtual int SetRenderPos(int x, int y, int w = 0, int h = 0) { mRenderX = x; mRenderY = y; if (w || h) { mRenderW = w; mRenderH = h; } return 0; }

	// GetPlacement - Returns the current placement
	virtual int GetPlacement(Placement& placement) { placement = mPlacement; return 0; }

	// SetPlacement - Update the current placement
	virtual int SetPlacement(Placement placement) { mPlacement = placement; return 0; }

	// SetPageFocus - Notify when a page gains or loses focus
	// TODO: This should be named NotifyPageFocus for consistency
	virtual void SetPageFocus(int inFocus __unused) { return; }

protected:
	int mRenderX, mRenderY, mRenderW, mRenderH;
	Placement mPlacement;
};

class ActionObject
{
public:
	ActionObject() { mActionX = 0; mActionY = 0; mActionW = 0; mActionH = 0; }
	virtual ~ActionObject() {}

public:
	// NotifyTouch - Notify of a touch event
	//  Return 0 on success, >0 to ignore remainder of touch, and <0 on error
	virtual int NotifyTouch(TOUCH_STATE state __unused, int x __unused, int y __unused) { return 0; }

	// NotifyKey - Notify of a key press
	//  Return 0 on success (and consume key), >0 to pass key to next handler, and <0 on error
	virtual int NotifyKey(int key __unused, bool down __unused) { return 1; }

	virtual int GetActionPos(int& x, int& y, int& w, int& h) { x = mActionX; y = mActionY; w = mActionW; h = mActionH; return 0; }

	//  Return 0 on success, <0 on error
	virtual int SetActionPos(int x, int y, int w = 0, int h = 0) {
		if (x < 0 || y < 0)
			return -1;

		mActionX = x;
		mActionY = y;
		if (w || h) {
			mActionW = w;
			mActionH = h;
		}
		return 0;
	}

	// IsInRegion - Checks if the request is handled by this object
	//  Return 1 if this object handles the request, 0 if not
	virtual int IsInRegion(int x, int y) { return ((x < mActionX || x >= mActionX + mActionW || y < mActionY || y >= mActionY + mActionH) ? 0 : 1); }

protected:
	int mActionX, mActionY, mActionW, mActionH;
};

class GUIObject
{
public:
	GUIObject(rapidxml::xml_node<>* node);
	virtual ~GUIObject();

public:
	bool IsConditionVariable(std::string var);
	bool isConditionTrue();
	bool isConditionValid();

	// NotifyVarChange - Notify of a variable change
	//  Returns 0 on success, <0 on error
	virtual int NotifyVarChange(const std::string& varName, const std::string& value);

protected:
	class Condition
	{
	public:
		Condition() {
			mLastResult = true;
		}

		std::string mVar1;
		std::string mVar2;
		std::string mCompareOp;
		std::string mLastVal;
		bool mLastResult;
	};

	std::vector<Condition> mConditions;

protected:
	static void LoadConditions(rapidxml::xml_node<>* node, std::vector<Condition>& conditions);
	static bool isMounted(std::string vol);
	static bool isConditionTrue(Condition* condition);
	static bool UpdateConditions(std::vector<Condition>& conditions, const std::string& varName);

	bool mConditionsResult;
};

class InputObject
{
public:
	InputObject() { HasInputFocus = 0; }
	virtual ~InputObject() {}

public:
	// NotifyCharInput - Notify of character input (usually from the onscreen or hardware keyboard)
	//  Return 0 on success (and consume key), >0 to pass key to next handler, and <0 on error
	virtual int NotifyCharInput(int ch __unused) { return 1; }

	virtual int SetInputFocus(int focus) { HasInputFocus = focus; return 1; }

protected:
	int HasInputFocus;
};

// Derived Objects

class HardwareKeyboard
{
public:
	HardwareKeyboard();
	virtual ~HardwareKeyboard();

public:
	// called by the input handler for key events
	int KeyDown(int key_code);
	int KeyUp(int key_code);

	// called by the input handler when holding a key down
	int KeyRepeat();

	// called by multi-key actions to suppress key-release notifications
	void ConsumeKeyRelease(int key);

	bool IsKeyDown(int key_code);
private:
	int mLastKey;
	int mLastKeyChar;
	std::set<int> mPressedKeys;
};

class MouseCursor : public RenderObject
{
public:
	MouseCursor(int posX, int posY);
	virtual ~MouseCursor();

	virtual int Render(void);
	virtual int Update(void);
	virtual int SetRenderPos(int x, int y, int w = 0, int h = 0);

	void Move(int deltaX, int deltaY);
	void GetPos(int& x, int& y);
	void LoadData(rapidxml::xml_node<>* node);
	void ResetData(int resX, int resY);

private:
	int m_resX;
	int m_resY;
	bool m_moved;
	float m_speedMultiplier;
	COLOR m_color;
	ImageResource *m_image;
	bool m_present;
};

#endif  // _OBJECTS_HEADER

