#pragma once
#include<Windows.h>

typedef struct _R3_Read_Memory {
	ULONG64 Pid;
	PUCHAR Read_Buffer;
	ULONG64 Address;
	ULONG64 Length;
}R3_Read_Memory, * PR3_Read_Memory;

BOOLEAN Apc_Read_Process_Memory_By_Pid(ULONG64 Pid, PUCHAR R3_Buffer, ULONG64 Address, ULONG64 Length);