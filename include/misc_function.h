/*
* File name   : MiscFunction.h
* Created     : 21.Mar.25
* Author      : dookyoon.kim
* Description : 
*/

#ifndef __MISC_FUNCTION_H__
#define __MISC_FUNCTION_H__

#include <iostream>
#include <string>
#include <chrono>

#include "types.h"

int IsExistDir(std::string& p_abs_path);
int RemoveFile(std::string& p_abs_path);
int ShowDurationTime(std::chrono::high_resolution_clock::time_point s, std::chrono::high_resolution_clock::time_point e);
std::string GetRandomString(int length = 10);

#endif
