#include"Head.h"


int main() {

	Connecting_Ring0();
	system("pause");
	
	ULONG64 time = 0;
	ULONG64 Mytime = 0;
	ULONG64 Nttime = 0;
	
	ULONG64 Mycs = 0;
	ULONG64 Ntcs = 0;

	DWORD PID = 0x1994;
	LPCVOID ADD = (LPCVOID)0x254DE0C6054;
	PUCHAR Mybuffer = (PUCHAR)malloc(0x1000);
	PUCHAR Ntbuffer = (PUCHAR)malloc(0x1000);
	ULONG64 Length = 30;
	if (Mybuffer == NULL || Ntbuffer == NULL)
		return 0;
	memset(Mybuffer, 0, 0x1000);
	memset(Ntbuffer, 0, 0x1000);

	Mytime = GetTickCount64();
	for (int i = 0; i < 1000000; i++) {
		if (!Apc_Read_Process_Memory_By_Pid(PID, Mybuffer, (ULONG64)ADD, Length)) {
			printf("无法读取！\n");
			break;
		}
		else {
			Mycs++;
		}
	}
	Mytime =  GetTickCount64() - Mytime;

	HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, 0x1994);
	
	Nttime = GetTickCount64();
	for (int i = 0; i < 1000000; i++) {
		if (!ReadProcessMemory(process, ADD, Ntbuffer, Length, NULL)) {
			printf("Nt无法读取！\n");
			break;
		}
		else {
			Ntcs++;
		}
	}
	Nttime =  GetTickCount64() - Nttime;




	printf("\nAPC读取内存%ld次总时间：%ld \n读取内存为：\n", Mycs, Mytime);
	for (int i = 0; i < Length; i++) {
		printf("%02X  ", Mybuffer[i]);
	}
	printf("\n");
	printf("\nReadProcessMemory读取内存%ld次总时间：%ld \n读取内存为：\n", Ntcs, Nttime);
	for (int i = 0; i < Length; i++) {
		printf("%02X  ", Ntbuffer[i]);
	}
	printf("\n");
	CloseHandle(process);
	CloseHandle(Test_Drv);
	system("pause");
}