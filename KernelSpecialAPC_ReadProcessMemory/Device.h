#pragma once
#include<ntifs.h>
#define my_device_name  L"\\Device\\APC_Drv"//设备名
#define my_link_name L"\\??\\APC_Drv"//符号链接名

#define TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x99f,METHOD_NEITHER,FILE_ANY_ACCESS)//功能测试


NTSTATUS Create_Device(PDRIVER_OBJECT DriverObject);

typedef struct _R3_Read_Memory {
	ULONG64 Pid;
	PUCHAR Read_Buffer;
	ULONG64 Address;
	ULONG64 Length;

}R3_Read_Memory,*PR3_Read_Memory;
