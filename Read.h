//---------------------------------------------------------------------------

#ifndef ReadH
#define ReadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class Read : public TThread
{
private:
protected:
	void __fastcall Execute();
public:
	__fastcall Read(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
