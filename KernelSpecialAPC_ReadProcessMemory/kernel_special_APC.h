#pragma once
#include<ntifs.h>


VOID Apc_Init();

//这个结构指针作为 kernelroutine 的参数
typedef struct _ReadMemory_Context {
	BOOLEAN Success;//是否成功读取
	UCHAR ErrorCode;//超时返回错误
	PUCHAR R0Buffer;//先读到这里，做缓冲区
	ULONG64 Address;//需要读取的地址
	ULONG64 Length;//需要读取的长度
}ReadMemory_Context,*PReadMemory_Context;


//通过PID对象读取内存
BOOLEAN Apc_Read_Process_Memory_By_Pid(ULONG64 Pid, PUCHAR R3_Buffer, ULONG64 Address, ULONG64 Length);

//通过EPROCESS对象读取内存
BOOLEAN Apc_Read_Process_Memory_By_Eprocess(PEPROCESS PEProcess, PUCHAR R3_Buffer, ULONG64 Address, ULONG64 Length);