## 通过插入内核特殊APC读取进程内存

### 优点：

无需获取进程句柄，无需挂靠进程（线程），无需切换CR3，让目标进程自己将内存交出来。

（There is no need to get the process handle, attach to the process (thread), switch CR3, and let the target process hand over the memory itself.）

### 缺点：

因为没有创建新的线程在目标进程上下文，所以，读取内存的时间相比挂靠进程（线程）的方式要慢上许多。（但也可以接受）

（Because no new thread is created in the context of the target process, the time of reading memory is much slower than that of attaching process (thread).(But it is also acceptable)）

![tsapctest](https://github.com/IcEy-999/Kernel-Special-APC-ReadProcessMemory/blob/main/Test%20picture/tsapctest.png)

**读取速度测试（Read speed test）**：

KernelSpecialAPC ：

读取 1000000 次长度为 30 字节的内存所需时间为：21985 ms

(Time required to read 1000000 times of memory with length of 30 bytes: 21985 ms)

ReadProcessMemory：

读取1000000 次长度为 30 字节的内存所需时间为：890 ms

(The time required to read 1000000 times of memory with a length of 30 bytes is: 890 ms)



**当进程全部线程被挂起时，无法读取内存！**

(Cannot read memory when all threads of the process are suspended!)



### **需要修改的地方（What needs to be modified）**：

一、 kernel_special_APC.c

```c
VOID Apc_Init() {
	PULONG64 P_KeInitializeApc = (PULONG64)&KeInitializeApc;
	PULONG64 P_KeInsertQueueApc = (PULONG64)&KeInsertQueueApc;

	//填入KeInitializeApc函数地址
	*P_KeInitializeApc = 0xfffff8042b62a530;

	//填入KeInsertQueueApc函数地址
	*P_KeInsertQueueApc = 0xfffff8042b63dc10;
}
```

二、Process_Thread.h

```c
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
```

关于如何动态获取上述 函数地址 和 结构偏移，请查看我的另一个项目：[Ntoskrnl_Viewer](https://github.com/IcEy-999/Ntoskrnl_Viewer)

For how to dynamically obtain the above function address and structure offset, please see my other project：[Ntoskrnl_Viewer](