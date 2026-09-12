//---------------------------------------------------------------------------

#ifndef TOcrThreadH
#define TOcrThreadH

#pragma once
#include <Classes.hpp>
#include <SysUtils.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>

class TOcrThread : public TThread
{
private:
	String FFileName;
	String FErrorMsg;
	String responseText;
	void __fastcall SyncFinish();
	void __fastcall SyncError();

protected:
	void __fastcall Execute();

public:
	TOcrThread(const String& AFileName);
};
//---------------------------------------------------------------------------
#endif
