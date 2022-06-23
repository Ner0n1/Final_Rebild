//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "Read.h"
#include "Sign.h"
#include "sqlite3.h"
#include <iostream>
#include <string.h>
#include "Iter.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall Read::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
bool Decor(BYTE* Value){
	if (Value[0] == 0x00) {
		return false;
	}
	return true;
}

void __fastcall Read::Error1()
{
	Form1->Label1->Caption = L"Error on Insert into!";
}

void __fastcall Read::Error2()
{
	Form1->Label1->Caption = L"Error on update table!";
}

__fastcall Read::Read(bool CreateSuspended, AFS* FS, bool Ignore, sqlite3* DB)
	: TThread(CreateSuspended), FS(FS), Ignore(Ignore), DB(DB)
{
	FreeOnTerminate = true;
	Iter = new class Iter(FS);
}
//---------------------------------------------------------------------------
void __fastcall Read::Execute()
{
    for(Iter->first();(!Iter->IsDone());Iter->next())
	 {
		if(Terminated)
		{
            break;
		}
		Value = Iter ->GetClusterContent();
		if(Ignore)
		{
			bool Dec = Decor(Value);
			if (!Dec)
			{
				continue;
			}
		}
		int sign = SigSearch(Value);
		if (sign != -1) {
			sqlite3_stmt* Stmt;
            std::wstring delrow = L"INSERT INTO Clusters (ClusterNumber, Signature) VALUES (" + std::to_wstring(Iter->GetClusterNumber());
			switch (sign) {
				case 0:
				delrow += L",\"jpeg\");";
				break;
				case 1:
				delrow += L",\"png\");";
				break;
				case 2:
				delrow += L",\"zip\");";
				break;
				case 3:
				delrow += L",\"rar\");";
				break;
				case 4:
				delrow += L",\"gzip\");";
				break;
				case 5:
                delrow += L",\"zip7\");";
				break;
			}
			const wchar_t* req = delrow.c_str();
			int res = sqlite3_prepare16_v2(DB, req, -1,
			&Stmt, NULL);
			if (res != SQLITE_OK)
			{
				Synchronize(&Error1);
			}else
			{
				res = sqlite3_step(Stmt);
				if(res != SQLITE_DONE)
				{
					Synchronize(&Error2);
				}
			}
			sqlite3_finalize(Stmt);
		}
	 }
}
//---------------------------------------------------------------------------


