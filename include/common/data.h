/*
	Copyright 2012 bigbiff/Dees_Troy TeamWin
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

#ifndef _DATAMANAGER_HPP_HEADER
#define _DATAMANAGER_HPP_HEADER

#include <pthread.h>
#include "common/infomanager.h"

class DataManager
{
public:
	static int ResetDefaults();
	static int LoadValues(const std::string& filename);
	static int Flush();

	// Core get routines
	static int GetValue(const std::string& varName, std::string& value);
	static int GetValue(const std::string& varName, int& value);
	static int GetValue(const std::string& varName, float& value);
	static unsigned long long GetValue(const std::string& varName, unsigned long long& value);

	// Helper functions
	static std::string GetStrValue(const std::string& varName);
	static int GetIntValue(const std::string& varName);

	// Core set routines
	static int SetValue(const std::string& varName, const std::string& value, const int persist = 0);
	static int SetValue(const std::string& varName, const int value, const int persist = 0);
	static int SetValue(const std::string& varName, const float value, const int persist = 0);
	static int SetValue(const std::string& varName, const unsigned long long& value, const int persist = 0);
	static int SetProgress(const float Fraction);
	static int ShowProgress(const float Portion, const float Seconds);

	static void DumpValues();
	static void update_tz_environment_variables();
	static void Vibrate(const std::string& varName);
	static void SetBackupFolder();
	static void SetDefaultValues();
	static void Output_Version(void); // Outputs the version to a file in the TWRP folder
	static void ReadSettingsFile(void);

	static std::string GetCurrentStoragePath(void);
	static std::string GetSettingsStoragePath(void);

protected:
	static std::string mBackingFile;
	static int mInitialized;
	static InfoManager mPersist;
	static InfoManager mData;
	static InfoManager mConst;

	static std::map<std::string, std::string> mConstValues;

protected:
	static int SaveValues();

	static int GetMagicValue(const std::string& varName, std::string& value);

private:
	static void sanitize_device_id(char* device_id);
	static void get_device_id(void);

	static pthread_mutex_t m_valuesLock;
};

#endif // _DATAMANAGER_HPP_HEADER

