//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "sqlite3.h"
#include "FS.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma resource "*.dfm"
TForm1 *Form1;
sqlite3* DB;
AFS* FS;
int id;
const wchar_t* path = L"\\\\.\\C:";
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	VirtualStringTree1 -> NodeDataSize = sizeof(Struct);
	sqlite3_stmt *stmt;
	int res = sqlite3_open16(L".\\DB.sqlite",&DB);
	if (res != SQLITE_OK) {
		Label1 -> Caption =L"Table is broken";
		Button1 -> Enabled = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    path = (Edit1->Text).c_str();
	FS = FactoryFS(path);

	Label7->Caption = UnicodeString(FS->GetOEM());
	Label8->Caption = UnicodeString(FS->GetBytesInSec());
	Label9->Caption = UnicodeString(FS->GetSectorsInCluster());
	Label10->Caption = UnicodeString(FS->GetBytesInCluster());
	Label11->Caption = UnicodeString(FS->GetNumberOfClusters());
	Button2 -> Enabled = true;
}
//---------------------------------------------------------------------------
