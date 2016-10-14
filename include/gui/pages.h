// pages.h - Base classes for page manager of GUI

#ifndef _PAGES_HEADER_HPP
#define _PAGES_HEADER_HPP

#include <vector>
#include <map>
#include <string>
#include "minzip/Zip.h"
#include "gui/objects.h"

struct language_struct {
	std::string filename;
	std::string displayvalue;
};

inline bool operator < (const language_struct& language1, const language_struct& language2)
{
	return language1.displayvalue < language2.displayvalue;
}

class Resource;
class ResourceManager;
class RenderObject;
class ActionObject;
class InputObject;
class MouseCursor;
class GUIObject;
class HardwareKeyboard;

class Page
{
public:
	Page(rapidxml::xml_node<>* page, std::vector<rapidxml::xml_node<>*> *templates);
	virtual ~Page();

	std::string GetName(void)   { return mName; }

public:
	virtual int Render(void);
	virtual int Update(void);
	virtual int NotifyTouch(TOUCH_STATE state, int x, int y);
	virtual int NotifyKey(int key, bool down);
	virtual int NotifyCharInput(int ch);
	virtual int SetKeyBoardFocus(int inFocus);
	virtual int NotifyVarChange(std::string varName, std::string value);
	virtual void SetPageFocus(int inFocus);

protected:
	std::string mName;
	std::vector<GUIObject*> mObjects;
	std::vector<RenderObject*> mRenders;
	std::vector<ActionObject*> mActions;
	std::vector<InputObject*> mInputs;

	ActionObject* mTouchStart;
	COLOR mBackground;

protected:
	bool ProcessNode(rapidxml::xml_node<>* page, std::vector<rapidxml::xml_node<>*> *templates, int depth);
};

struct LoadingContext;

class PageSet
{
public:
	PageSet();
	virtual ~PageSet();

public:
	int Load(LoadingContext& ctx, const std::string& filename);
	int LoadLanguage(char* languageFile, ZipArchive* package);
	void MakeEmergencyConsoleIfNeeded();

	Page* FindPage(std::string name);
	int SetPage(std::string page);
	int SetOverlay(Page* page);
	const ResourceManager* GetResources();

	// Helper routine for identifing if we're the current page
	int IsCurrentPage(Page* page);
	std::string GetCurrentPage() const;

	// These are routing routines
	int Render(void);
	int Update(void);
	int NotifyTouch(TOUCH_STATE state, int x, int y);
	int NotifyKey(int key, bool down);
	int NotifyCharInput(int ch);
	int SetKeyBoardFocus(int inFocus);
	int NotifyVarChange(std::string varName, std::string value);

	void AddStringResource(std::string resource_source, std::string resource_name, std::string value);

protected:
	int LoadDetails(LoadingContext& ctx, rapidxml::xml_node<>* root);
	int LoadPages(LoadingContext& ctx, rapidxml::xml_node<>* pages);
	int LoadVariables(rapidxml::xml_node<>* vars);

protected:
	ResourceManager* mResources;
	std::vector<Page*> mPages;
	Page* mCurrentPage;
	std::vector<Page*> mOverlays; // Special case for popup dialogs and the lock screen
};

class PageManager
{
public:
	// Used by GUI
	static char* LoadFileToBuffer(std::string filename, ZipArchive* package);
	static void LoadLanguageList(ZipArchive* package);
	static void LoadLanguage(std::string filename);
	static int LoadPackage(std::string name, std::string package, std::string startpage);
	static PageSet* SelectPackage(std::string name);
	static int ReloadPackage(std::string name, std::string package);
	static void ReleasePackage(std::string name);
	static int RunReload();
	static void RequestReload();
	static void SetStartPage(const std::string& page_name);

	// Used for actions and pages
	static int ChangePage(std::string name);
	static int ChangeOverlay(std::string name);
	static const ResourceManager* GetResources();
	static std::string GetCurrentPage();

	// Helper to identify if a particular page is the active page
	static int IsCurrentPage(Page* page);

	// These are routing routines
	static int Render(void);
	static int Update(void);
	static int NotifyTouch(TOUCH_STATE state, int x, int y);
	static int NotifyKey(int key, bool down);
	static int NotifyCharInput(int ch);
	static int SetKeyBoardFocus(int inFocus);
	static int NotifyVarChange(std::string varName, std::string value);

	static MouseCursor *GetMouseCursor();
	static void LoadCursorData(rapidxml::xml_node<>* node);

	static HardwareKeyboard *GetHardwareKeyboard();

	static rapidxml::xml_node<>* FindStyle(std::string name);
	static void AddStringResource(std::string resource_source, std::string resource_name, std::string value);

protected:
	static PageSet* FindPackage(std::string name);
	static void LoadLanguageListDir(std::string dir);
	static void Translate_Partition(const char* path, const char* resource_name, const char* default_value);
	static void Translate_Partition(const char* path, const char* resource_name, const char* default_value, const char* storage_resource_name, const char* storage_default_value);
	static void Translate_Partition_Display_Names();

protected:
	static std::map<std::string, PageSet*> mPageSets;
	static PageSet* mCurrentSet;
	static MouseCursor *mMouseCursor;
	static HardwareKeyboard *mHardwareKeyboard;
	static bool mReloadTheme;
	static std::string mStartPage;
	static LoadingContext* currentLoadingContext;
};

#endif  // _PAGES_HEADER_HPP
