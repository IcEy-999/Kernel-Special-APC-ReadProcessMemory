#include "Process_Thread.h"


BOOLEAN Get_pEprocess_By_Pid(ULONG64 Pid, PEPROCESS* pProcess) {
	PEPROCESS CurrentEprocess = IoGetCurrentProcess();
	PLIST_ENTRY64 P_ProcessListEntry = (PLIST_ENTRY64)((ULONG64)CurrentEprocess+ ProcessListEntry);
	PLIST_ENTRY64 LS = P_ProcessListEntry->Flink;
	PEPROCESS targetProcess = NULL;
	ULONG64 num = 0;//要是找了500个进程都找不到，就返回错误。（或者查询链表时其他线程有对链表的操作）
	BOOLEAN Find = FALSE;
	__try {
		while (LS != P_ProcessListEntry && num <500)
		{
			targetProcess = (ULONG64)LS - ProcessListEntry;
			if (*((PULONG64)((ULONG64)targetProcess + UniqueProcessId)) == Pid) {
				*pProcess = targetProcess;
				Find = TRUE;
				break;
			}
			LS = LS->Flink;
			num++;
		}
	}except(1) {
		return Find;
	}
	return Find;
}

BOOLEAN Get_APC_pThread_By_Process(PEPROCESS Process, PETHREAD* pThread) {
	PETHREAD targetThread = NULL;
	PLIST_ENTRY64 P_ThreadListHead = (PLIST_ENTRY64)((ULONG64)Process + ThreadListHead);
	PLIST_ENTRY64 LS = P_ThreadListHead->Blink;
	BOOLEAN Find = FALSE;
	__try {
		while (LS != P_ThreadListHead)
		{
			targetThread = (ULONG64)LS - ThreadListEntry;
			if (*(PUCHAR)((ULONG64)targetThrean + Running) == TRUE && *(PUSHORT)((ULONG64)targetThrean + SpecialApcDisable) == 0) {
				//线程正在运行 并且 未关闭APC
				*pThread = targetThread;
				Find = TRUE;
				break;
			}

			LS = LS->Blink;
			//num++;
		}
	}except(1) {
		return Find;
	}
	return Find;
}
