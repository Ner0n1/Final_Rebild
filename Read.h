//---------------------------------------------------------------------------

#ifndef ReadH
#define ReadH
#include "Read.h"
#include "FS.h"
#include "sqlite3.h"
#include "Iter.h"
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class Read : public TThread
{
private:
protected:
	AFS* FS;
	bool Ignore;
	Iter* Iter;
	BYTE* Value;
	sqlite3* DB;
	void __fastcall Error1();
	void __fastcall Error2();
	void __fastcall Execute();
public:
	__fastcall Read(bool CreateSuspended, AFS* FS, bool Ignore, sqlite3* DB);
};
//---------------------------------------------------------------------------
#endif
