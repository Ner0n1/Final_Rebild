//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "sqlite3.h"
#include "FS.h"
#include "Read.h"
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
	Memo1 -> Clear();
	Memo1-> Lines -> Add(UnicodeString(FS->GetOEM()));
	Memo1-> Lines -> Add(L"Byte in sector: " +
	UnicodeString(FS->GetBytesInSec()));
	Memo1-> Lines -> Add(L"Sectors in cluster: "+UnicodeString(FS->GetSecInCluster()));
	Memo1-> Lines -> Add(L"Bytes in cluster: "+UnicodeString(FS->GetBytesInCluster()));
	Memo1-> Lines -> Add(L"Total clusters: "+ UnicodeString(FS->GetNumberOfClusters()));
	Button3 -> Enabled = true;
	bool Ignore = CheckBox1 -> Checked;
	ReadT = new Read(false, FS, Ignore, DB);

}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button3Click(TObject *Sender)
{
	ReadT -> Terminate();
	VirtualStringTree1 -> Clear();
	VirtualStringTree1 -> BeginUpdate();
	sqlite3_stmt *Stmt;
	int res = sqlite3_prepare16_v2(DB, L"SELECT * FROM Clusters ORDER BY ClusterNumber", -1, &Stmt, NULL);
	while (true)
	{
		res = sqlite3_step(Stmt);
		if(res == SQLITE_DONE) break;
		else if (res== SQLITE_ROW)
		{
			PVirtualNode Node = VirtualStringTree1 -> AddChild(VirtualStringTree1 -> RootNode);
			Struct *nodeData = (Struct*)VirtualStringTree1 -> GetNodeData(Node);
			nodeData -> ClusterNumber = sqlite3_column_int(Stmt,0);
			nodeData -> Sig = (UnicodeString)(char*)sqlite3_column_text(Stmt,1);
		}
		else
		{
			Label1 -> Caption = L"Error in update table!";
			break;
		}

	}
	sqlite3_finalize(Stmt);
	VirtualStringTree1 -> EndUpdate();

	Button4 -> Enabled = false;
	CheckBox1 -> Enabled = true;
	Button3 -> Enabled = true;
	Button5 -> Enabled = true;
	Button1 -> Enabled = true;
	Edit1 -> Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::VirtualStringTree1GetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)

{
	if(!Node) return;
	Struct *nodeData = (Struct*)VirtualStringTree1 -> GetNodeData(Node);

		switch (Column) {

			case 0:
			{
				CellText = UnicodeString(nodeData -> ClusterNumber);  break;
			}
			case 1:
			{
				CellText = nodeData -> Sig; break;
			}
        }
}

//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
    VirtualStringTree1->Clear();
	sqlite3_stmt *Stmt;
	int res = sqlite3_prepare16_v2(DB, L"DELETE FROM Clusters;", -1,
	&Stmt, NULL);
	if (res != SQLITE_OK)
	{
		Label1 -> Caption = L"Error while delete!";
		return;
	}

	res = sqlite3_step(Stmt);
	if(res != SQLITE_DONE)
	{
		Label1 -> Caption = L"Error trying delete!";
		return;
	}
	sqlite3_finalize(Stmt);
}

//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
	sqlite3_stmt *Stmt;
	std::wstring delrow = L"DELETE FROM Clusters WHERE ClusterNumber = "
	+ std::to_wstring(id) + L";";
	const wchar_t* req = delrow.c_str();
	int res = sqlite3_prepare16_v2(DB, req, -1, &Stmt, NULL);
	if(res != SQLITE_OK)
	{
		Label1->Caption = L"Error in DELETE FROM DB";
		return;
	}
	res = sqlite3_step(Stmt);

	if(res != SQLITE_DONE)
	{
		Label1->Caption = L"Error while delete!";
		return;
	}
	sqlite3_finalize(Stmt);

	VirtualStringTree1 -> Clear();
	VirtualStringTree1 -> BeginUpdate();
	res = sqlite3_prepare16_v2(DB, L"SELECT * FROM Clusters ORDER BY ClusterNumber;",
	 -1, &Stmt, NULL);
	while (true)
	{
		res = sqlite3_step(Stmt);
		if(res == SQLITE_DONE) break;
		else if (res == SQLITE_ROW)
		{
			PVirtualNode Node = VirtualStringTree1 -> AddChild(VirtualStringTree1 -> RootNode);
			Struct *nodeData = (Struct*)VirtualStringTree1 -> GetNodeData(Node);
			nodeData -> ClusterNumber = sqlite3_column_int(Stmt,0);
			nodeData -> Sig = (UnicodeString)(char*)sqlite3_column_text(Stmt,1);
			}
		else
		{
			Label1 -> Caption = L"Error in update table";
			break;
		}

	}
	sqlite3_finalize(Stmt);
	VirtualStringTree1 -> EndUpdate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::VirtualStringTree1AddToSelection(TBaseVirtualTree *Sender,
          PVirtualNode Node)
{
    if (!Node) return;
	Button4 -> Enabled = True;
	Struct *nodeData = (Struct*)VirtualStringTree1 -> GetNodeData(Node);
	id = nodeData -> ClusterNumber;
}
//---------------------------------------------------------------------------

