/*
* File name   : MonotorApp.h
* Created     : 21.Mar.25
* Author      : dookyoon.kim
* Description : 
*/
#ifndef MONITOR_APP_H
#define MONITOR_APP_H

#include <iostream>
#include <atomic>
#include <string>

#include "types.h"

class LogManager;

class MonitorApp {
public:
	MonitorApp(void);
	virtual ~MonitorApp(void);

	int AllocationLogManager(int field_count = 2);
	int IsValidLogMan(void);

	int CreateManuallyAddThread(void);
	int WakeUpManuallyAddThread(void);
	int DestroyManuallyAddThread(void);
	void ThreadFuncManuallyAdd(std::mutex* p_mtx, std::condition_variable *p_cv, std::atomic<int>* p_status, LogManager* p_log_man);

	int CreateAutoAddThread(void);
	int WakeUpAutoAddThread(void);
	int DestroyAutoAddThread(void);
	void ThreadFuncAutoAdd(std::mutex* p_mtx, std::condition_variable *p_cv, std::atomic<int>* p_status, LogManager* p_log_man);

	std::thread			thread_insert_manual;
	std::thread			thread_insert_auto;

	std::mutex			mutex_insert_manual;
	std::mutex			mutex_insert_auto;

	std::atomic<int>	status_thread_manual = TRUE;
	std::atomic<int>	status_thread_auto = TRUE;

	std::condition_variable		cond_manually_thread;
	std::condition_variable		cond_auto_thread;

protected:

private:
	LogManager*  mp_log_man;

};

#endif
