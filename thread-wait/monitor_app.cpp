/*
* File name   : MonitorApp.cpp
* Created     : 21.Mar.25
* Author      : dookyoon.kim
* Description : This file defines major function and type.
*/

#include <filesystem>
#include <mutex>
#include <condition_variable>
#include <thread>

#include "debug.h"
#include "misc_function.h"

#include "monitor_app.h"
#include "log_manager.h"

MonitorApp::MonitorApp(void)
{
}

MonitorApp::~MonitorApp(void)
{
}

int MonitorApp::AllocationLogManager(int field_count)
{
	mp_log_man = new LogManager(field_count);

	if (mp_log_man == nullptr) {
		mgh_error("Failed to alloc log_manager class \n");
		return FALSE;
	}

	return TRUE;
}

int MonitorApp::IsValidLogMan(void)
{
	int ret = TRUE;
	if (mp_log_man == nullptr) {
		ret = FALSE;
	}
	return ret;
}

void MonitorApp::ThreadFuncManuallyAdd(std::mutex *p_mtx, std::condition_variable *p_cv, std::atomic<int>* p_status, LogManager* p_log_man)
{
	std::unique_lock<std::mutex> lock(*p_mtx);
	int status_val = FALSE;
	bool  is_valid_thread = false;

	status_val = p_status->load();

	if (status_val == TRUE) {
		is_valid_thread = true;
	}

	while (is_valid_thread == true)
	{
		mgh_debug("[Worker] wait. (%d)\n", p_status->load());
		p_cv->wait(lock);

		status_val = p_status->load();
		if (status_val == FALSE) {
			break;
		}

		mgh_debug("[Worker] recv sig and start.\n");

		// start insert db-data.
		p_log_man->InsertData();

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	mgh_debug("[Worker] end.\n");
}
 
int MonitorApp::CreateManuallyAddThread(void)
{
	int ret = TRUE;
	bool is_valid_thread = true;

	do {
		if (mp_log_man == nullptr) {
			mgh_error("Not alloc Log-manager class\n");
			ret = FALSE;
			break;
		}
		status_thread_manual.store(TRUE);

		thread_insert_manual = std::thread([this]() {
				this->ThreadFuncManuallyAdd(
						&this->mutex_insert_manual,
						&this->cond_manually_thread,
						&this->status_thread_manual,
						this->mp_log_man);
				});

		is_valid_thread = thread_insert_manual.joinable();

		if (is_valid_thread == true) {
			mgh_info("suc to create thread.\n");
			thread_insert_manual.detach();
		} else {
			mgh_error("Failed to create thread.\n");
			ret = FALSE;
			break;
		}
	} while (0);

	return ret;
}

int MonitorApp::WakeUpManuallyAddThread(void)
{
	if (mp_log_man == nullptr) {
		mgh_error("Not alloc Log-manager class\n");
		return FALSE;
	}

	mgh_debug("notify to thread \n");
	cond_manually_thread.notify_one();

	return TRUE;
}

int MonitorApp::DestroyManuallyAddThread(void)
{
	if (mp_log_man == nullptr) {
		mgh_error("Not alloc Log-manager class\n");
		return FALSE;
	}

	mgh_debug("change status  (%d)->FALSE\n", status_thread_manual.load());

	status_thread_manual.store(FALSE);
	cond_manually_thread.notify_one();

	return TRUE;
}

int MonitorApp::CreateAutoAddThread(void)
{
	int ret = TRUE;
	bool is_valid_thread = true;

	do {
		if (mp_log_man == nullptr) {
			mgh_error("Not alloc Log-manager class\n");
			ret = FALSE;
			break;
		}

		status_thread_auto.store(TRUE);

		thread_insert_auto = std::thread([this]() {
				this->ThreadFuncAutoAdd(
						&this->mutex_insert_auto,
						&this->cond_auto_thread,
						&this->status_thread_auto,
						this->mp_log_man);
				});

		is_valid_thread = thread_insert_auto.joinable();

		if (is_valid_thread == true) {
			mgh_info("suc to create thread.\n");
			thread_insert_auto.detach();
		} else {
			mgh_error("Failed to create thread.\n");
			ret = FALSE;
			break;
		}
	} while (0);

	return ret;
}

int MonitorApp::WakeUpAutoAddThread(void)
{
	if (mp_log_man == nullptr) {
		mgh_error("Not alloc Log-manager class\n");
		return FALSE;
	}

	mgh_debug("notify to thread \n");
	cond_auto_thread.notify_one();

	return TRUE;
}

int MonitorApp::DestroyAutoAddThread(void)
{
	if (mp_log_man == nullptr) {
		mgh_error("Not alloc Log-manager class\n");
		return FALSE;
	}

	mgh_debug("change status  (%d)->(%d)\n", status_thread_auto.load(), FALSE);

	status_thread_auto.store(FALSE);
	return TRUE;
}

void MonitorApp::ThreadFuncAutoAdd(std::mutex *p_mtx, std::condition_variable *p_cv, std::atomic<int>* p_status, LogManager* p_log_man)
{
	std::unique_lock<std::mutex> lock(*p_mtx);
	int status_val = FALSE;
	bool  is_valid_thread = false;

	mgh_debug("[Worker] wait. (%d)\n", p_status->load());
	p_cv->wait(lock);
	mgh_debug("[Worker] recv sig and start.\n");

	status_val = p_status->load();

	if (status_val == TRUE) {
		is_valid_thread = true;
	}

	while (is_valid_thread == true)
	{
		// start insert db-data.
		p_log_man->InsertData();
		status_val = p_status->load();

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	mgh_debug("[Worker] end.\n");
}
 
