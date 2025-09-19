/*
* File name   : MiscFunction.cpp
* Created     : 21.Mar.25
* Author      : dookyoon.kim
* Description : 
*/


#include <filesystem>
#include <random>

#include "misc_function.h"
#include "debug.h"

int IsExistDir(std::string& p_abs_path)
{
	int ret = TRUE;
	std::filesystem::path dir_str(p_abs_path);

	if (std::filesystem::exists(dir_str.parent_path()) && std::filesystem::is_directory(dir_str.parent_path())) {
		// nothing.
	} else {
		ret = FALSE;
	}

	return ret;
}

int RemoveFile(std::string& p_abs_path)
{
	int ret = TRUE;

	if ([&p_abs_path]() { return std::filesystem::exists(p_abs_path); }()) {
		if (std::filesystem::remove(p_abs_path)) {
			std::cerr << "success delete file(" << p_abs_path << ")\n";
		} else {
			ret = FALSE;
		}
	} else {
		std::cerr << "There is no file.(" << p_abs_path << ")\n";
		ret = FALSE;
	}

	return ret;
}


int ShowDurationTime(std::chrono::high_resolution_clock::time_point start, std::chrono::high_resolution_clock::time_point end)
{
	auto dur_microsec = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	mgh_debug("Durarion: %ld.%ld sec\n", dur_microsec.count() / 1000000, dur_microsec.count());

	return TRUE;
}

std::mt19937 g_gen_str(std::random_device{}());
std::uniform_int_distribution<> g_char_dist(0,61);

std::string GetRandomString(int length)
{
	const std::string str_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	std::string result;

	result.reserve(length);

	for (int i = 0; i < length; ++i) {
		result += str_table[g_char_dist(g_gen_str)];
	}

	return result;
}
