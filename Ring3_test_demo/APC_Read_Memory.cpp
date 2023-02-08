#include"Head.h"


BOOLEAN Apc_Read_Process_Memory_By_Pid(ULONG64 Pid, PUCHAR R3_Buffer, ULONG64 Address, ULONG64 Length) {
	R3_Read_Memory test = { 0 };
	test.Pid = Pid;
	test.Address = Address;
	test.Length = Length;
	test.Read_Buffer = R3_Buffer;
	DWORD lent = 0;
	if (!DeviceIoControl(Test_Drv, TEST, NULL, 0, &test, sizeof(R3_Read_Memory), &lent, NULL)) {
		printf("devio error !!!\n");
		return FALSE;
	}
	if(lent!=1){
		return FALSE;
	}
	return TRUE;
	
}