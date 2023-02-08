#pragma once
#include <Windows.h>
#include <iostream>
#define DEVICE_NAME L"\\\\.\\APC_Drv" //符号链接名

#define TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x99f,METHOD_NEITHER,FILE_ANY_ACCESS)//功能测试



extern HANDLE Test_Drv;


BOOLEAN Connecting_Ring0();