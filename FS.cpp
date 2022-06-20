//---------------------------------------------------------------------------

#pragma hdrstop

#include "FS.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
AFS::AFS(const wchar_t* path)
{
	Handle = CreateFileW(target, GENERIC_READ,
	FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0,NULL);
}

NTFS::NTFS(const wchar_t* target) :AFS(path)
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
	NTFS *ptrNTFS = (NTFS*)Block;
	BytesInSec = ptrNTFS -> BytesInSec;
	SecInCluster = ptrNTFS-> SecInCluster;
	BytesPerCluster =  BytesPerSector*SectorsPerCluster;
	OEM = L"NTFS";
	NumOfClusters = (ptrNTFS -> NumberOfSectors)/SecInCluster;
}

FAT32::FAT32(const wchar_t* target) : AFS(path)
{

	DWORD bytesRead;
	DWORD bytes = 512;
	BYTE Block[512];
	LARGE_INTEGER offset;
	offset.QuadPart = 0;

	unsigned long pos = SetFilePointer(DiskHandle, offset.LowPart,
	&offset.HighPart, FILE_BEGIN);
	if (pos != offset.LowPart)
	{
	   Form1 -> Label1 -> Caption = L"Error while seting position!";
	   CloseHandle(Handle);
	}

	bool ReadSec = ReadFile(DiskHandle, Block, bytes, &bytesRead, NULL);
	if (ReadSec == false || bytesRead != bytes)
	{
	   Form1 -> Label1 -> Caption = L"Error while read!";
	   CloseHandle(Handle);
	}

	FAT32 *ptrFAT32 = (FAT32*)Block;
	BytesInSec = ptrFAT32 -> BytesInSec;
	SecInCluster = ptrFAT32 -> SecInCluster;
	BytesInCluster =  BytesInSec*SecInCluster;
	OEM = L"FAT32";
	if (ptrFAT32->LargeSectors != 0)
	{
		 NumOfClusters = (ptrFAT32->LargeSectors)/SecInCluster;
	}
	else
	{
		 NumOfClusters = (ptrFAT32->SmallSectors)/SecInCluster;
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
	return NumberOfClusters;
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
	AbstractFS* FS;

	HANDLE Handle = CreateFileW(target, GENERIC_READ,
	FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0,NULL);

	if (Handle == INVALID_HANDLE_VALUE)
	{
	   Form1 -> Label1 -> Caption = L"Error while open disk!";
	   CloseHandle(Handle);
	}

	unsigned long pos = SetFilePointer(Handle, offset.LowPart,
	&offset.HighPart, FILE_BEGIN);
	if (pos != offset.LowPart) {
	   Form1 -> Label1 -> Caption = L"Error while set position!";
	   CloseHandle(Handle);
	}

	bool ReadSec = ReadFile(Handle, Block, bytes, &bytesRead, NULL);
	if (ReadSec == false || bytesRead != bytes){
		Form1 -> Label1 -> Caption = L"Error while reading!";
		CloseHandle(Handle);
	}
	AFS *ptrAFS = (AFS*)Block;
	CloseHandle(Handle);

	if (strstr(ptrAFS ->OEM,"NTFS"))
	{
	   FS = new NTFS(path);
	}
	else if (strstr(ptrAbstract_FS -> OEM,"MSDOS5.0"))
	{
	   FS = new FAT32(path);
	}
	else
	{
	   Form1 -> Label1 -> Caption = L"Unknown fs type!";
	}
	return FS;
}
