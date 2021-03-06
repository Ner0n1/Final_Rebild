//---------------------------------------------------------------------------

#pragma hdrstop

#include "FS.h"
#include "Unit1.h"
#include <cstring>
//---------------------------------------------------------------------------
#pragma package(smart_init)
AFS::AFS(const wchar_t* path)
{
	Handle = CreateFileW(path, GENERIC_READ,
	FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0,NULL);
}

NTFS::NTFS(const wchar_t* path) : AFS(path)
{
	DWORD bytesRead;
	DWORD bytes = 512;
	BYTE Block[512];
	LARGE_INTEGER offset;
	offset.QuadPart = 0;

	unsigned long pos = SetFilePointer(Handle, offset.LowPart,
	&offset.HighPart, FILE_BEGIN);
	if (pos != offset.LowPart)
	{
	   Form1 -> Label1 -> Caption = L"Error while seting position!";
	   CloseHandle(Handle);
	}

	bool ReadSec = ReadFile(Handle, Block, bytes, &bytesRead, NULL);
	if (ReadSec == false || bytesRead != bytes)
	{
	   Form1 -> Label1 -> Caption = L"Error while read!";
	   CloseHandle(Handle);
	}
	NTFS_BR *ptrNTFS = (NTFS_BR*)Block;
	BytesInSec = ptrNTFS -> BytesInSec;
	SecInCluster = ptrNTFS-> SecInCluster;
	BytesInCluster =  BytesInSec*SecInCluster;
	OEM = L"NTFS";
	NumOfClusters = (ptrNTFS -> NumberOfSectors)/SecInCluster;
}

FAT32::FAT32(const wchar_t* path) : AFS(path)
{

	DWORD bytesRead;
	DWORD bytes = 512;
	BYTE Block[512];
	LARGE_INTEGER offset;
	offset.QuadPart = 0;

	unsigned long pos = SetFilePointer(Handle, offset.LowPart,
	&offset.HighPart, FILE_BEGIN);
	if (pos != offset.LowPart)
	{
	   Form1 -> Label1 -> Caption = L"Error while seting position!";
	   CloseHandle(Handle);
	}

	bool ReadSec = ReadFile(Handle, Block, bytes, &bytesRead, NULL);
	if (ReadSec == false || bytesRead != bytes)
	{
	   Form1 -> Label1 -> Caption = L"Error while read!";
	   CloseHandle(Handle);
	}

	FAT32_BR *ptrFAT32 = (FAT32_BR*)Block;
	BytesInSec = ptrFAT32 -> BytesInSec;
	SecInCluster = ptrFAT32 -> SecInCluster;
	BytesInCluster =  BytesInSec*SecInCluster;
	OEM = L"FAT32";
	if (ptrFAT32->LargeSec != 0)
	{
		 NumOfClusters = (ptrFAT32->LargeSec)/SecInCluster;
	}
	else
	{
		 NumOfClusters = (ptrFAT32->SmallSec)/SecInCluster;
	}
}

HANDLE AFS::GetHandle()
{
	return Handle;
}
unsigned long AFS::GetBytesInSec(){
	return BytesInSec;
}
unsigned long AFS::GetBytesInCluster(){
	return BytesInCluster;
}
unsigned long AFS::GetSecInCluster(){
	return SecInCluster;
}
unsigned long AFS::GetNumberOfClusters(){
	return NumOfClusters;
}
const wchar_t* AFS::GetOEM(){
	return OEM;
}

AFS* FactoryFS(const wchar_t* path)
{
	DWORD bytesRead;
	DWORD bytes = 512;
	BYTE Block[512];
	LARGE_INTEGER offset;
	offset.QuadPart = 0;
	AFS* FS;

	HANDLE Handle = CreateFileW(path, GENERIC_READ,
	FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0,NULL);

	if (Handle == INVALID_HANDLE_VALUE)
	{
	   Form1 -> Label1 -> Caption = L"Error while open disk!";
	   CloseHandle(Handle);
	}

	unsigned long pos = SetFilePointer(Handle, offset.LowPart,
	&offset.HighPart, FILE_BEGIN);
	if (pos != offset.LowPart)
	{
	   Form1 -> Label1 -> Caption = L"Error while set position!";
	   CloseHandle(Handle);
	}

	bool ReadSec = ReadFile(Handle, Block, bytes, &bytesRead, NULL);
	if (ReadSec == false || bytesRead != bytes)
	{
		Form1 -> Label1 -> Caption = L"Error while reading!";
		CloseHandle(Handle);
	}
	AbsFS *ptrAFS = (AbsFS*)Block;
	if (strstr(ptrAFS ->OEM,"NTFS"))
	{
	   FS = new NTFS(path);
	}
	else if (strstr(ptrAFS -> OEM,"MSDOS5.0"))
	{
	   FS = new FAT32(path);
	}
	else
	{
	   Form1 -> Label1 -> Caption = L"Unknown fs type!";
	}
	CloseHandle(Handle);
	return FS;
}
