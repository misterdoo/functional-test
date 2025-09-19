/*
* File name   : LogManager.cpp
* Created     : 21.Mar.25
* Author      : dookyoon.kim
* Description : 
*/

#include <filesystem>
#include <sstream>

#include "log_manager.h"
#include "debug.h"


LogManager::LogManager(int field_cnt)
	:m_field_count(field_cnt)
{
	mgh_info("constructor log manager class. field count(%d) \n", field_cnt);
	std::string str_db_file_path(std::filesystem::current_path());

	Open(str_db_file_path);
}

LogManager::~LogManager(void)
{
	mgh_debug("exit log manager.\n");
}

int LogManager::Open(std::string& abs_path_db_file)
{
	int ret = TRUE;

	mgh_debug("Open. path(%s)\n", abs_path_db_file.c_str());

	return ret;
}

int LogManager::InsertData(int max_count)
{
	int ret = TRUE;

	mgh_info("Insert Data.\n");

	return ret;
}

