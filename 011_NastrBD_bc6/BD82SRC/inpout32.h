#pragma once

//Functions exported from DLL.
//For easy inclusion is user projects.
//Original InpOut32 function support
//void	_stdcall Out32(short PortAddress, short data);
/*extern "C"*/ void __declspec(dllimport) Out32(short PortAddress, short data);
short	_stdcall Inp32(short PortAddress);

//My extra functions for making life easy
BOOL	_stdcall IsInpOutDriverOpen();  //Returns TRUE if the InpOut driver was opened successfully
BOOL	_stdcall IsXP64Bit();			//Returns TRUE if the OS is 64bit (x64) Windows.

//DLLPortIO function support
UCHAR   _stdcall DlPortReadPortUchar (USHORT port);
void    _stdcall DlPortWritePortUchar(USHORT port, UCHAR Value);

USHORT  _stdcall DlPortReadPortUshort (USHORT port);
void    _stdcall DlPortWritePortUshort(USHORT port, USHORT Value);

ULONG	_stdcall DlPortReadPortUlong(ULONG port);
void	_stdcall DlPortWritePortUlong(ULONG port, ULONG Value);

//WinIO function support (Untested and probably does NOT work - esp. on x64!)
PBYTE	_stdcall MapPhysToLin(PBYTE pbPhysAddr, DWORD dwPhysSize, HANDLE *pPhysicalMemoryHandle);
bool	_stdcall UnmapPhysicalMemory(HANDLE PhysicalMemoryHandle, PBYTE pbLinAddr);
bool	_stdcall GetPhysLong(PBYTE pbPhysAddr, PDWORD pdwPhysVal);
bool	_stdcall SetPhysLong(PBYTE pbPhysAddr, DWORD dwPhysVal);





