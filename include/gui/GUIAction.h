#pragma once

#include "gui/objects.h"

// GUIAction - Used for standard actions
class GUIAction : public GUIObject, public ActionObject
{
	friend class ActionThread;

public:
	GUIAction(rapidxml::xml_node<>* node);

public:
	virtual int NotifyTouch(TOUCH_STATE state, int x, int y);
	virtual int NotifyKey(int key, bool down);
	virtual int NotifyVarChange(const std::string& varName, const std::string& value);

	int doActions();

protected:
	class Action
	{
	public:
		std::string mFunction;
		std::string mArg;
	};

	std::vector<Action> mActions;
	std::map<int, bool> mKeys;

protected:
	enum ThreadType { THREAD_NONE, THREAD_ACTION, THREAD_CANCEL };

	int getKeyByName(std::string key);
	int doAction(Action action);
	ThreadType getThreadType(const Action& action);
	void simulate_progress_bar(void);
	int flash_zip(std::string filename, int* wipe_cache);
	void reinject_after_flash();
	void operation_start(const std::string operation_name);
	void operation_end(const int operation_status);
	time_t Start;

	// map action name to function pointer
	typedef int (GUIAction::*execFunction)(std::string);
	typedef std::map<std::string, execFunction> mapFunc;
	static mapFunc mf;
	static std::set<std::string> setActionsRunningInCallerThread;

	// GUI actions
	int reboot(std::string arg);
	int home(std::string arg);
	int key(std::string arg);
	int page(std::string arg);
	int reload(std::string arg);
	int readBackup(std::string arg);
	int set(std::string arg);
	int clear(std::string arg);
	int mount(std::string arg);
	int unmount(std::string arg);
	int restoredefaultsettings(std::string arg);
	int copylog(std::string arg);
	int compute(std::string arg);
	int setguitimezone(std::string arg);
	int overlay(std::string arg);
	int queuezip(std::string arg);
	int cancelzip(std::string arg);
	int queueclear(std::string arg);
	int sleep(std::string arg);
	int appenddatetobackupname(std::string arg);
	int generatebackupname(std::string arg);
	int checkpartitionlist(std::string arg);
	int getpartitiondetails(std::string arg);
	int screenshot(std::string arg);
	int setbrightness(std::string arg);

	// (originally) threaded actions
	int fileexists(std::string arg);
	int flash(std::string arg);
	int wipe(std::string arg);
	int refreshsizes(std::string arg);
	int nandroid(std::string arg);
	int fixcontexts(std::string arg);
	int fixpermissions(std::string arg);
	int dd(std::string arg);
	int partitionsd(std::string arg);
	int installhtcdumlock(std::string arg);
	int htcdumlockrestoreboot(std::string arg);
	int htcdumlockreflashrecovery(std::string arg);
	int cmd(std::string arg);
	int terminalcommand(std::string arg);
	int killterminal(std::string arg);
	int reinjecttwrp(std::string arg);
	int checkbackupname(std::string arg);
	int decrypt(std::string arg);
	int adbsideload(std::string arg);
	int adbsideloadcancel(std::string arg);
	int openrecoveryscript(std::string arg);
	int installsu(std::string arg);
	int fixsu(std::string arg);
	int decrypt_backup(std::string arg);
	int repair(std::string arg);
	int resize(std::string arg);
	int changefilesystem(std::string arg);
	int startmtp(std::string arg);
	int stopmtp(std::string arg);
	int flashimage(std::string arg);
	int cancelbackup(std::string arg);
	int checkpartitionlifetimewrites(std::string arg);
	int mountsystemtoggle(std::string arg);
	int setlanguage(std::string arg);
	int twcmd(std::string arg);
	int addlog(std::string arg);

	int simulate;
};


