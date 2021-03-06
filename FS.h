//---------------------------------------------------------------------------

#ifndef FSH
#define FSH
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma pack(push,1)
 typedef struct
 {
	BYTE indent1[3];
	char OEM[8];
	USHORT BytesInSec;
	BYTE SecInCluster;
	BYTE indent2[10];
	UINT16 SectorsPerTrack;
	UINT16 NumberOfHeads;
	BYTE indent3[12];
	ULONGLONG NumberOfSectors;
	ULONGLONG MFTClusterNumber;
	ULONGLONG CopyMFTClusterNumber;
	UINT MFTSize;
	UINT BuffSize;
	BYTE indent4[3];
	ULONGLONG SerialNumber;
	USHORT Checksum;
  } NTFS_BR;

  typedef struct
  {
	BYTE indent1[3];
	char OEM[8];
	USHORT BytesInSec;
	BYTE SecInCluster;
	BYTE FATTables;
	USHORT Root;
	USHORT SmallSec;
	BYTE MediaTyoe;
	USHORT TableSec;
	USHORT SectorsPerTrack;
	USHORT NumberOfHeads;
	BYTE indent2[4];
	ULONG LargeSec;
	BYTE DiskNumber;
	BYTE indent3;
	BYTE Signature;
	BYTE SerialNumber[4];
	BYTE Label[11];
	ULONGLONG ID;
  } FAT32_BR;

  typedef struct
  {
	  BYTE indent[3];
      char OEM[8];
  } AbsFS;

  class AFS
{
	protected:
		HANDLE Handle;
		unsigned long BytesInSec;
		unsigned long BytesInCluster;
		unsigned long SecInCluster;
		unsigned long NumOfClusters;
	public:
		HANDLE GetHandle();
		unsigned long GetBytesInSec();
		unsigned long GetBytesInCluster();
		unsigned long GetSecInCluster();
		unsigned long GetNumberOfClusters();
		const wchar_t* GetOEM();
		AFS(const wchar_t* path);
		const wchar_t* OEM;

};

class FAT32: public AFS{
	public:
		FAT32(const wchar_t* path);
};

class NTFS: public AFS{
	public:
		NTFS(const wchar_t* path);
};

AFS*  FactoryFS(const wchar_t* path);
#endif
