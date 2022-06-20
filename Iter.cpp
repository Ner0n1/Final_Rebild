//---------------------------------------------------------------------------

#pragma hdrstop

#include "Unit1.h"
#include "Iter.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Iter::Iter(AFS* FS)
	:ClusterNumber(0), NumberOfClusters(FS->GetNumberOfClusters()), Done(false), FS(FS)
{
	ClusterContent = new BYTE[FS->GetBytesInCluster()];
}
void Iter::first()
{
	ClusterNumber = 0;
}
void Iter::next()
{
	ClusterNumber++;
}
bool Iter::IsDone()
{
	return Done;
}
bool Iter::HardDone()
{
	Done = true;
    return Done;
}
unsigned long Iter::GetClusterNumber()
{
	return ClusterNumber;
}

BYTE* Iter::GetClusterContent()
{
	DWORD BytesRead;
	LARGE_INTEGER Offset;
	Offset.QuadPart = ClusterNumber*FS->GetBytesInCluster();

	unsigned long pos = SetFilePointer(FS->GetHandle(), Offset.LowPart,
	&Offset.HighPart, FILE_BEGIN);
	if (pos != Offset.LowPart)
	{
	   Form1 -> Label1 -> Caption = L"Iterator Error while seting pos!";
	   return ClusterContent;
	}

	bool Read = ReadFile(FS->GetHandle(), ClusterContent, FS->GetBytesInCluster(),
	&BytesRead, NULL);
	if (Read == false || BytesRead != FS->GetBytesInCluster())
	{
	   Form1 -> Label1 -> Caption = L"Iterator Error while read!";
	}
	return ClusterContent;
}
