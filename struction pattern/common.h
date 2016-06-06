#ifndef _COMMON_H_
#define _COMMON_H_

/*
** FileName      : common.h
** Author        : Frank Tly
** Date          : 2015/7/19
** Description   : Struction Pattern Common Header File
*/

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>

using namespace std;
#define  NULL_POINTER(ptr) (NULL == ptr)
#define  SAFE_RELASE_POINTER(ptr) if(!NULL_POINTER(ptr)) {delete ptr; ptr = NULL;}


#endif