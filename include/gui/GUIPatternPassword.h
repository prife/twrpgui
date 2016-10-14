#pragma once

#include "gui/objects.h"

class GUIAction;
class GUIPatternPassword : public GUIObject, public RenderObject, public ActionObject
{
public:
	GUIPatternPassword(rapidxml::xml_node<>* node);
	virtual ~GUIPatternPassword();

public:
	virtual int Render(void);
	virtual int Update(void);
	virtual int NotifyTouch(TOUCH_STATE state, int x, int y);
	virtual int NotifyVarChange(const std::string& varName, const std::string& value);
	virtual int SetRenderPos(int x, int y, int w = 0, int h = 0);

protected:
	void CalculateDotPositions();
	void ResetActiveDots();
	void ConnectDot(int dot_idx);
	void ConnectIntermediateDots(int dot_idx);
	void Resize(size_t size);
	int InDot(int x, int y);
	bool DotUsed(int dot_idx);
	std::string GeneratePassphrase();
	void PatternDrawn();

	struct Dot {
		int x;
		int y;
		bool active;
	};

	std::string mSizeVar;
	size_t mGridSize;

	Dot* mDots;
	int* mConnectedDots;
	size_t mConnectedDotsLen;
	int mCurLineX;
	int mCurLineY;
	bool mTrackingTouch;
	bool mNeedRender;

	COLOR mDotColor;
	COLOR mActiveDotColor;
	COLOR mLineColor;
	ImageResource *mDotImage;
	ImageResource *mActiveDotImage;
	gr_surface mDotCircle;
	gr_surface mActiveDotCircle;
	int mDotRadius;
	int mLineWidth;

	std::string mPassVar;
	GUIAction *mAction;
	int mUpdate;
};

