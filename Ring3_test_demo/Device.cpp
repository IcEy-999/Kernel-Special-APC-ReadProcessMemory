#include "Head.h"

HANDLE Test_Drv = NULL;


BOOLEAN Connecting_Ring0() {
	Test_Drv = CreateFile(DEVICE_NAME, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_SYSTEM, NULL);
	if (Test_Drv == INVALID_HANDLE_VALUE)
	{
		DWORD Error_Code = GetLastError();
		CloseHandle(Test_Drv);
		printf("Connecting_Ring0 ERROR£º%d", Error_Code);
		return FALSE;
	}
	return TRUE;

}
