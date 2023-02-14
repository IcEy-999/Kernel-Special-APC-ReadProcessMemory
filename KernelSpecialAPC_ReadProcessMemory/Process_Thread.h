#pragma once
#include<ntifs.h>


enum  Eprocess_Members_Offset //自己想办法获取进程结构偏移
{
	ThreadListHead = 0x30,//线程链表
	ProcessListEntry = 0x240,//进程链表
	UniqueProcessId = 0x2e0,//进程PID

};

enum Ethread_Members_Offset //自己想办法获取线程结构偏移
{
	Running = 0x71,
	SpecialApcDisable = 0x1e6,
	ThreadListEntry = 0x2f8,
};

BOOLEAN Get_pEprocess_By_Pid(ULONG64 Pid, PEPROCESS* pProcess);

BOOLEAN Get_APC_pThread_By_Process(PEPROCESS Process, PETHREAD* pThread);
