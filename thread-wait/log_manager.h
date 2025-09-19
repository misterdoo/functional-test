/*
* File name   : LogManager.h
* Created     : 21.Mar.25
* Author      : dookyoon.kim
* Description : 
*/

#ifndef LOG_MANAGER_H
#define LOG_MANAGER_H

#include <iostream>
#include <string>
#include <atomic>

#include "types.h"

class LogManager
{
public:
	LogManager(int field_cnt);
	virtual ~LogManager(void);

	int InsertData(int max_count = 1);

protected:

private:
	std::atomic<int>	m_log_index = 0;
	int					m_field_count;

	int		Open(std::string& abs_path_db_file);
};

#endif
