//---------------------------------------------------------------------------
#include "FS.h"
#include "Unit1.h"
#ifndef IterH
#define IterH
//---------------------------------------------------------------------------
class Iter
{
	protected:
	   unsigned long ClusterNumber;
	   BYTE* ClusterContent;
	   unsigned long NumberOfClusters;
	   bool Done;
	   AbstractFS* FS;
	public:
        Iterator(AFS* FS);
		unsigned long GetClusterNumber();
		BYTE* GetClusterContent();
		bool IsDone();
		bool HardDone();
		void first();
		void next();

};

#endif
